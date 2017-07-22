#pragma once

#include "../graphics.h"

class Graphics;
class Game;
class GameSprite;
class MikeRectangle;


class UnitSelectCursor
{

private:

	const int   TEXTURE_WIDTH = 32; 
	const int   TEXTURE_HEIGHT = 32; 
 

	int	x;
	int    y;
	UINT         width;
	UINT         height;
	RECT        rect;

	bool    initialized;

	Graphics * graphics;
	GameSprite * gameSprite;

  public:

	UnitSelectCursor(Graphics *g);
    virtual ~UnitSelectCursor();


	virtual void Draw();

	void update(float frameTime);
	void setX(int newX) { this->x = newX; }
	void setY(int newY) { this->y = newY; }

	MikeRectangle * shpBoundingRectangle;
	boolean drawShpBoundingRectangle;


	
};



