#include "GameSprite.h"

#include "graphics.h"
#include "Circle.h"
#include "ShpFile.h"
#include "PaletteFile.h"
#include "ImageHeader.h"
#include "PaletteEntry.h"



//* Refactor code
// X	* Use different ctors for ShpFile and image file
//	* Pull code into class
//* Use Shp File for UnitSelection cursor
//* Fix drawing of bounding box
//	* Consider just selecting center of image, whatever the size, and just drawing it, minigunner and unit selection curos
//	* Graph out on graph paper



GameSprite::GameSprite(LPDIRECT3DDEVICE9 device, ShpFile & shpFile, D3DCOLOR transparentColor) {
	this->device = device;
	this->InitializeTextureWithShpFile(shpFile);
	this->InitializeSprite("");
}


GameSprite::GameSprite(LPDIRECT3DDEVICE9 device, std::string file, D3DCOLOR transparentColor) {
	this->device = device;
	this->InitializeTexture( file, transparentColor);
	this->InitializeSprite(file);
}


GameSprite::~GameSprite() {
}


const DWORD point_fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;


const int g_width = 50;
const int g_height = 39;


struct point_vertex {
	float x, y, z, rhw;  // The transformed(screen space) position for the vertex.
	DWORD colour;        // The vertex colour.
};


point_vertex minigunnerImageData[g_width * g_height]; //A whole whack of data


int mapColorIndex(int index) {
	return index;
}


void GameSprite::InitializeTextureWithShpFile(ShpFile & shpFile) {

	ImageHeader * header0 = shpFile.ImageHeaders()[0];
	std::vector<unsigned char> & byteBuffer0 = header0->GetData();

	PaletteFile paletteFile(std::string("assets/temperat.pal"));
	std::vector<PaletteEntry *> & paletteEntries = paletteFile.GetPaletteEntries();

	width = g_width;
	height = g_height;

	int currentIndex = 0;
	int numPoints = 0;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			unsigned char nextByte = byteBuffer0[currentIndex];
			if (nextByte != 0) {
				int index = nextByte;

				index = mapColorIndex(index);
				PaletteEntry * paletteEntry = paletteEntries[index];

				int intRed = paletteEntry->GetRed();
				int intGreen = paletteEntry->GetGreen();
				int intBlue = paletteEntry->GetBlue();

				float fRed = (float)paletteEntry->GetRed() / 63.0f * 255.0f;
				float fGreen = (float)paletteEntry->GetGreen() / 63.0f * 255.0f;
				float fBlue = (float)paletteEntry->GetBlue() / 63.0f  * 255.0f;

				intRed = fRed;
				intGreen = fGreen;
				intBlue = fBlue;

				minigunnerImageData[currentIndex].x = x;
				minigunnerImageData[currentIndex].y = y;
				minigunnerImageData[currentIndex].z = 1.0f;
				minigunnerImageData[currentIndex].rhw = 1.0f;
				minigunnerImageData[currentIndex].colour = D3DCOLOR_XRGB(intRed, intGreen, intBlue);
				int red = rand() % 255;
				int green = rand() % 255;
				int blue = rand() % 255;

				int mike = 9;
				numPoints++;

			}
			else {
				minigunnerImageData[currentIndex].x = x;
				minigunnerImageData[currentIndex].y = y;
				minigunnerImageData[currentIndex].z = 1.0f;
				minigunnerImageData[currentIndex].rhw = 1.0f;
				minigunnerImageData[currentIndex].colour = D3DCOLOR_RGBA(0, 0, 0, 0);
			}
			currentIndex++;
		}
	}


	//initialize_data();


	UINT usage = D3DUSAGE_RENDERTARGET;
	width = g_width;
	height = g_height;

	HRESULT result = D3DXCreateTexture(
		device,      // Associated Direct3D device.
		width, height, // Dimensions of surface in pixels we render to.
		1,      // Number of mipmap levels.

		usage,           // How the texture will be used.
		D3DFMT_UNKNOWN,      // Texture format (i.e., D3DFORMAT).
		D3DPOOL_DEFAULT, // Render targets must be in default pool.
		&texture);         // Returns pointer to texture.
	if (result != D3D_OK) {
		throw("Failed calling D3DXCreateTexture()");
	}


	LPDIRECT3DSURFACE9 g_renderSurface;
	D3DSURFACE_DESC desc;
	texture->GetSurfaceLevel(0, &g_renderSurface);
	g_renderSurface->GetDesc(&desc);


	ID3DXRenderToSurface * g_renderTarget;
	result = D3DXCreateRenderToSurface(device, desc.Width, desc.Height, desc.Format, TRUE, D3DFMT_D16, &g_renderTarget);
	if (FAILED(result))
		throw("Failed calling D3DXCreateRenderToSurface()");

	g_renderTarget->BeginScene(g_renderSurface, NULL);
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	device->SetFVF(point_fvf);

	void *data = minigunnerImageData;

	device->DrawPrimitiveUP(D3DPT_POINTLIST,        //PrimitiveType
		//g_width,                //PrimitiveCount
		//numPoints,                //PrimitiveCount
		g_width * g_height,
		data,                   //pVertexStreamZeroData
		sizeof(point_vertex));  //VertexStreamZeroStride

	g_renderTarget->EndScene(0);


}


void GameSprite::InitializeTexture(std::string filename, D3DCOLOR transparentColor) {
	// Get width and height from file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (result != D3D_OK) {
		//throw(GameError(gameErrorNS::FATAL_ERROR, "Failed calling D3DXGetImageInfoFromFile()"));
		throw("Failed calling D3DXGetImageInfoFromFile()");
	}

	width = info.Width;
	height = info.Height;

	// Create the new texture by loading from file
	result = D3DXCreateTextureFromFileEx(
		device,           //3D device
		filename.c_str(),           //image filename
		info.Width,         //texture width
		info.Height,        //texture height
		1,                  //mip-map levels (1 for no chain)
		0,                  //usage
		D3DFMT_UNKNOWN,     //surface format (default)
		D3DPOOL_DEFAULT,    //memory class for the texture
		D3DX_FILTER_POINT,       //image filter
		D3DX_FILTER_NONE,       //mip filter
		transparentColor,
		&info,              //bitmap file info (from loaded file)
		NULL,               //color palette
		&texture);         //destination texture
	if (FAILED(result)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed calling D3DXCreateTextureFromFileEx()"));
	}

}

bool GameSprite::InitializeSprite(std::string file) {

	bool success = true;
	try {
		HRESULT     result;         // standard Windows return codes
		result = D3DXCreateSprite(device, &sprite);
		if (FAILED(result))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D sprite"));

		spriteCenter = D3DXVECTOR2((float)(width / 2),
			(float)(height / 2));


		//float overallScaling = 5.0f;
		float overallScaling = 4.0f;

		// Original C&C resolution was 640 x 400, which is what the original artwork was scaled for
		// But current actual screen resolution is being set to  640 x 480
		// 400 is 83.33333 percent of 480
		// So multiply desired scaling by 0.8333333 to get actual scaled height

		float widthAdjustmentAmount = 400.0f / 480.0f;
		float actualWidthScaling = overallScaling * widthAdjustmentAmount;
		float actualHeightScaling = overallScaling;
		//scaling = D3DXVECTOR2(actualWidthScaling, actualHeightScaling);
		scaling = D3DXVECTOR2(overallScaling, overallScaling);


	}
	catch (...) { return false; }
	initialized = true;                    // set true when initialized
	return success;
}


void GameSprite::Draw(float gameTime, D3DXVECTOR2 position) {

	D3DCOLOR color = graphicsNS::WHITE;

	if (texture == NULL)
		return;

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	LPDIRECT3DDEVICE9 device3d = device;
	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	device3d->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, false);

	device3d->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device3d->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	D3DXVECTOR2 translate = position;
	float xOffset = this->width / 2.0f;
	float yOffset = this->height / 2.0f;
	translate.x = translate.x - xOffset;
	translate.y = translate.y - yOffset;
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		&spriteCenter,               // keep origin at top left when scaling
		0.0f,               // no scaling rotation
		&scaling,           // scale amount
		&spriteCenter,      // rotation center
		(float)0,			// rotation angle
		&translate);        // X,Y location


	sprite->SetTransform(&matrix);

	sprite->Draw(texture, NULL, NULL, NULL, color);
	sprite->End();

}

