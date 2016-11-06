#include "Mushroom.h"
#include "graphics.h"



const char TEXTURES_IMAGE[] = "pictures\\m3.png";  // game textures

Mushroom::Mushroom(Graphics *g, int width, int height)
{

	x = mushroomNS::X;
	y = mushroomNS::Y;

	velocity.x = 300.0;
	//velocity.y = 300.0;
	velocity.y = 0.0;

    rect.left = 0;       
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;

	graphics = g;

	this->width = width;
	this->height = height;

	InitializeTexture(TEXTURES_IMAGE);

	if (!this->initializeSprite(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite"));


	rect.left = 0;
	rect.right = rect.left + width;
	rect.top = 0;
	rect.bottom = rect.top + height;

}

void Mushroom::InitializeTexture(std::string filename) {
	// Get width and height from file
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	if (result != D3D_OK) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed calling D3DXGetImageInfoFromFile()"));
	}

	width = info.Width;
	height = info.Height;

	// Create the new texture by loading from file
	result = D3DXCreateTextureFromFileEx(
		graphics->get3Ddevice(),           //3D device
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

Mushroom::~Mushroom()
{
}


void Mushroom::update(float frameTime)
{
	x += frameTime * velocity.x;
	y += frameTime * velocity.y;

	int boundingBoxWidth = 16 * 3;
	int boundingBoxHeight = 16 * 3;

	if ((x + boundingBoxWidth) > GAME_WIDTH)              // if off right screen edge
		velocity.x = -velocity.x;
	else if (x - boundingBoxWidth < -mushroomNS::WIDTH)     // else if off left screen edge
		velocity.x = -velocity.x;
	if (y + boundingBoxHeight > GAME_HEIGHT)             // if off bottom screen edge
		velocity.y = -velocity.y;
	else if (y - boundingBoxHeight < -mushroomNS::HEIGHT)    // else if off top screen edge
		velocity.y = -velocity.y;
}



bool Mushroom::initializeSprite(Graphics *g, std::string file)
{
	this->graphics = g;
	bool success = true;
	try {
		HRESULT     result;         // standard Windows return codes
		result = D3DXCreateSprite(g->get3Ddevice(), &sprite);
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





void Mushroom::draw()
{
    if ( graphics == NULL)
        return;


    this->drawSprite(graphicsNS::WHITE);        // use color as filter
}

void Mushroom::drawSprite( COLOR_ARGB color)
{
	if (texture == NULL)
		return;

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	LPDIRECT3DDEVICE9 device3d = graphics->get3Ddevice();
	device3d->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	device3d->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, false);

	device3d->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	device3d->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);



	int roundedX = x;
	int roundexY = y;
//	D3DXVECTOR2 translate = D3DXVECTOR2((float)x, (float)y);
	D3DXVECTOR2 translate = D3DXVECTOR2((float)roundedX, (float)roundexY);
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

	sprite->Draw(texture, &rect, NULL, NULL, color);
	sprite->End();

}




