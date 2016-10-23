#include "Mushroom.h"
#include "graphics.h"
#include "Texture.h"


const char TEXTURES_IMAGE[] = "pictures\\m1.png";  // game textures

Mushroom::Mushroom(Graphics *g, int width, int height)
{

	x = mushroomNS::X;              // location on screen
	y = mushroomNS::Y;

	velocity.x = 300.0;
	velocity.y = 300.0;

    rect.left = 0;       // used to select one frame from multi-frame image
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;

	graphics = g;                               // the graphics object

	this->width = width;
	this->height = height;

	texture = new Texture(graphics, TEXTURES_IMAGE);

	if (!this->initializeSprite(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sprite"));


	rect.left = 0;
	rect.right = rect.left + width;
	rect.top = 0;
	rect.bottom = rect.top + height;

}

Mushroom::~Mushroom()
{}


void Mushroom::update(float frameTime)
{
	//x += frameTime * velocity.x;
	//y += frameTime * velocity.y;

	if ((x + mushroomNS::WIDTH) > GAME_WIDTH)              // if off right screen edge
		velocity.x = -velocity.x;
	else if (x - mushroomNS::WIDTH < -mushroomNS::WIDTH)     // else if off left screen edge
		velocity.x = -velocity.x;
	if (y + mushroomNS::HEIGHT > GAME_HEIGHT)             // if off bottom screen edge
		velocity.y = -velocity.y;
	else if (y - mushroomNS::HEIGHT < -mushroomNS::HEIGHT)    // else if off top screen edge
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

		scaling = D3DXVECTOR2(0.833, 1);


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

	device3d->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	device3d->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	device3d->SetSamplerState(2, D3DSAMP_MAGFILTER, D3DTEXF_NONE);

	device3d->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	device3d->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	device3d->SetSamplerState(2, D3DSAMP_MIPFILTER, D3DTEXF_NONE);



	D3DXVECTOR2 translate = D3DXVECTOR2((float)x, (float)y);
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


	sprite->Draw(texture->getDirextXTexture(), &rect, NULL, NULL, color);
	sprite->End();

}




