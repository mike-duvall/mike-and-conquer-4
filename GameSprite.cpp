#include "GameSprite.h"

#include "graphics.h"



GameSprite::GameSprite() {

}


GameSprite::~GameSprite() {

}


bool GameSprite::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height) {

	this->device = device;
	this->InitializeTexture( file);
	this->InitializeSprite(file);

	return true;

}


void GameSprite::InitializeTexture(std::string filename) {
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
		D3DX_DEFAULT,       //image filter
		D3DX_DEFAULT,       //mip filter
		graphicsNS::TRANSCOLOR,         //color key for transparency
		&info,              //bitmap file info (from loaded file)
		NULL,               //color palette
		&texture);         //destination texture
	if (FAILED(result)) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed calling D3DXCreateTextureFromFileEx()"));
	}

}

bool GameSprite::InitializeSprite(std::string file)
{

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


void GameSprite::Draw(float gameTime, D3DXVECTOR2 position)
//void Mushroom::drawSprite(COLOR_ARGB color)
{

	COLOR_ARGB color = graphicsNS::WHITE;

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
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		NULL,               // keep origin at top left when scaling
		0.0f,               // no scaling rotation
		&scaling,           // scale amount
		&spriteCenter,      // rotation center
		(float)0,			// rotation angle
		&translate);        // X,Y location


	sprite->SetTransform(&matrix);

	sprite->Draw(texture, NULL, NULL, NULL, color);
	sprite->End();

}

