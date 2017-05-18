#include "UnitSelectCursor.h"
#include "graphics.h"


#include "GameSprite.h"
#include "ShpFile.h"

const std::string IMAGE_FILE = "pictures\\cursor.png";  // game textures

UnitSelectCursor::UnitSelectCursor(Graphics *g)
{

	x = 500;
	y = 500;

	this->width = TEXTURE_WIDTH;
	this->height = TEXTURE_HEIGHT;

    rect.left = 0;       
    rect.top = 0;
    rect.right = width;
    rect.bottom = height;

	graphics = g;

	ShpFile shpFile(std::string("assets/select.shp"));
	int imageIndex = 1;
	gameSprite = new GameSprite(graphics->Get3Ddevice(), shpFile, graphicsNS::WHITE, imageIndex);

	rect.left = 0;
	rect.right = rect.left + width;
	rect.top = 0;
	rect.bottom = rect.top + height;

}


UnitSelectCursor::~UnitSelectCursor()
{
}





void UnitSelectCursor::draw()
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


