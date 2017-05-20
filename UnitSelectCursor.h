#pragma once

#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "graphics.h"

class Graphics;
class Game;
class GameSprite;
class MikeRectangle;


class UnitSelectCursor
{



private:

	const int   TEXTURE_WIDTH = 32; 
	const int   TEXTURE_HEIGHT = 32; 
 

	float       x;
	float       y;
	UINT         width;
	UINT         height;
	RECT        rect;

	bool    initialized;

	Graphics * graphics;
	GameSprite * gameSprite;

  public:

	UnitSelectCursor(Graphics *g);
    virtual ~UnitSelectCursor();


	virtual void draw();

	void update(float frameTime);
	void setX(float newX) { this->x = newX; }
	void setY(float newY) { this->y = newY; }

	MikeRectangle * shpBoundingRectangle;
	boolean drawShpBoundingRectangle;


	
};



