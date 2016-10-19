#pragma once

#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "graphics.h"

class Graphics;
class Game;
class Texture;

namespace mushroomNS
{
	//const int   WIDTH = 128;                // image width
	//const int   HEIGHT = 128;               // image height
	const int   WIDTH = 50;                // image width
	const int   HEIGHT = 39;               // image height

	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
}



class Mushroom
{

public:
  

	float       x;
	float       y;
	UINT         width;
	UINT         height;
	D3DXVECTOR2 velocity;
	RECT        rect;


	bool    initialized;

	Graphics *graphics;
	Texture * texture;


	bool initializeSprite(Graphics *g, std::string file);

	LPD3DXSPRITE   sprite;
	D3DXVECTOR2 spriteCenter;
	D3DXVECTOR2 scaling;

	void drawSprite(COLOR_ARGB color = graphicsNS::WHITE);


  public:

    Mushroom(Graphics *g, int width, int height);
    virtual ~Mushroom();


	virtual void draw();

	void update(float frameTime);
	virtual const D3DXVECTOR2 getVelocity() const { return velocity; }
	virtual void  setVelocity(D3DXVECTOR2 v) { velocity = v; }
	void setX(float newX) { this->x = newX; }
	void setY(float newY) { this->y = newY; }

	
};



