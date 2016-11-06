#include "Mushroom.h"
#include "graphics.h"


#include "GameSprite.h"

const std::string IMAGE_FILE = "pictures\\m3.png";  // game textures

Minigunner::Minigunner(Graphics *g, int width, int height)
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

	gameSprite = new GameSprite(g->get3Ddevice(), IMAGE_FILE, this->width, this->height);

	rect.left = 0;
	rect.right = rect.left + width;
	rect.top = 0;
	rect.bottom = rect.top + height;

}


Minigunner::~Minigunner()
{
}


void Minigunner::update(float frameTime)
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



void Minigunner::draw()
{
    if ( graphics == NULL)
        return;

	D3DXVECTOR2 position;

	int roundedX = (int) x;
	int roundexY = (int) y;

	position.x = (float)roundedX;
	position.y = (float)roundexY;
	gameSprite->Draw(0, position);

}


