#include "GameSprite.h"

#include "graphics.h"
#include "Circle.h"
#include "ShpFile.h"
#include "PaletteFile.h"
#include "ImageHeader.h"
#include "PaletteEntry.h"


GameSprite::~GameSprite() {
}


GameSprite::GameSprite(LPDIRECT3DDEVICE9 device, std::string file, int width, int height, D3DCOLOR transparentColor) {
	this->device = device;
	if (file.size() > 0) {
		this->InitializeTexture( file, transparentColor);
	}
	else {
		this->InitializeTextureWithShpFile();
	}
	//this->InitializeTextureWithCircle();
	this->InitializeSprite(file);
}





void GameSprite::InitializeTextureWithCircle() {
	UINT usage = D3DUSAGE_RENDERTARGET;
	width = 16;
	height = 16;
	//Just changed this to 16 16
	//	Figure out how 16,16 tranlates to 50,39, actual size of the shp file image

	//This is basically working, now read and render minigunner from image

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
	if(FAILED(result))
		throw("Failed calling D3DXCreateRenderToSurface()");

	g_renderTarget->BeginScene(g_renderSurface, NULL);
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	Circle myCircle(8, 8);
	myCircle.Draw(device);
	g_renderTarget->EndScene(0);


}


const DWORD point_fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;


//const int g_width = 640;
//const int g_height = 480;

const int g_width = 50;
const int g_height = 39;


struct point_vertex {
	float x, y, z, rhw;  // The transformed(screen space) position for the vertex.
	DWORD colour;        // The vertex colour.
};


point_vertex minigunnerImageData[g_width * g_height]; //A whole whack of data


void initialize_data(void) {
	int count;
	float count_f;
	unsigned char red, green, blue;
	float y;

	srand(GetTickCount());
	for (count = 0; count<g_width; count++) {
		minigunnerImageData[count].x = (float)(rand() % g_width);
		minigunnerImageData[count].y = (float)(rand() % g_height);
		minigunnerImageData[count].z = 1.0f;
		minigunnerImageData[count].rhw = 1.0f;
		minigunnerImageData[count].colour = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
	}

}



int mapColorIndex(int index) {
	return index;
}


void GameSprite::InitializeTextureWithShpFile() {


	ShpFile shpFile(std::string("assets/e1.shp"));

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
			//if (!byteBuffer0.hasRemaining()) {
			//	continue;
			//}

			unsigned char nextByte = byteBuffer0[currentIndex];
			if (nextByte != 0) {
				//int index = Byte.toUnsignedInt(nextByte);
				int index = nextByte;

				index = mapColorIndex(index);
				PaletteEntry * paletteEntry = paletteEntries[index];

				//float red = paletteEntry->GetRed() / 63.0f;
				//float green = paletteEntry->GetGreen() / 63.0f;
				//float blue = paletteEntry->GetBlue() / 63.0f;

				int intRed = paletteEntry->GetRed();
				int intGreen = paletteEntry->GetGreen();
				int intBlue = paletteEntry->GetBlue();

				float fRed = (float)paletteEntry->GetRed() / 63.0f * 255.0f;
				float fGreen = (float)paletteEntry->GetGreen() / 63.0f * 255.0f;
				float fBlue = (float)paletteEntry->GetBlue() / 63.0f  * 255.0f;

				intRed = fRed;
				intGreen = fGreen;
				intBlue = fBlue;



				//Color color = new Color(red, green, blue, 1);

				//pixmap.setColor(color);

				//pixmap.drawPixel(x, y);
				minigunnerImageData[currentIndex].x = x;
				minigunnerImageData[currentIndex].y = y;
				minigunnerImageData[currentIndex].z = 1.0f;
				minigunnerImageData[currentIndex].rhw = 1.0f;
				minigunnerImageData[currentIndex].colour = D3DCOLOR_XRGB(intRed, intGreen, intBlue);
				//minigunnerImageData[currentIndex].colour = D3DCOLOR_ARGB(255, intRed, intGreen, intBlue);
				int red = rand() % 255;
				int green = rand() % 255;
				int blue = rand() % 255;
				//minigunnerImageData[currentIndex].colour = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
				//minigunnerImageData[currentIndex].colour = D3DCOLOR_XRGB(red, green, blue);

				//This is essentially working, but minigunner is way too dark
				//	Figure out how to fix

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



	//int roundedX = x;
	//int roundexY = y;
	//	D3DXVECTOR2 translate = D3DXVECTOR2((float)x, (float)y);
	//D3DXVECTOR2 translate = D3DXVECTOR2((float)roundedX, (float)roundexY);
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

