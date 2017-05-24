#include "UnitSelectCursor.h"
#include "graphics.h"


#include "GameSprite.h"
#include "ShpFile.h"
#include "MikeRectangle.h"


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
	boolean animate = false;
	gameSprite = new GameSprite(graphics->Get3Ddevice(), shpFile, graphicsNS::WHITE);

	std::vector<unsigned int> standingStillAnimationSequence;
	standingStillAnimationSequence.push_back(1);
	gameSprite->AddAnimationSequence(0, standingStillAnimationSequence);
	gameSprite->SetCurrentAnimationSequenceIndex(0);


	gameSprite->SetSpriteCenter(15, 15);

	rect.left = 0;
	rect.right = rect.left + width;
	rect.top = 0;
	rect.bottom = rect.top + height;

	drawShpBoundingRectangle = false;
	shpBoundingRectangle = new MikeRectangle(x, y, gameSprite->GetWidth(), gameSprite->GetHeight());


}


UnitSelectCursor::~UnitSelectCursor()
{
}





void UnitSelectCursor::Draw()
{

	gameSprite->Draw(0, x, y);


	if (drawShpBoundingRectangle) {
		shpBoundingRectangle->SetX(this->x);
		shpBoundingRectangle->SetY(this->y);
		shpBoundingRectangle->Draw(graphics->Get3Ddevice());
	}

}


