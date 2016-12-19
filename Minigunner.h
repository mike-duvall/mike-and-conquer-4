#pragma once

#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "graphics.h"

class Graphics;
class Game;
class GameSprite;

//namespace mushroomNS
//{
//
//	const int   WIDTH = 16;                // image width
//	const int   HEIGHT = 16;               // image height
//
//
//	const int   X = GAME_WIDTH / 2 - WIDTH / 2; // location on screen
//	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2;
//}



class Minigunner
{

private: 

	const int   WIDTH = 16;                // image width
	const int   HEIGHT = 16;               // image height

  

	float       x;
	float       y;
	UINT         width;
	UINT         height;
	D3DXVECTOR2 velocity;
	RECT        rect;


	bool    initialized;

	Graphics * graphics;
	GameSprite * gameSprite;


  public:

	Minigunner(Graphics *g);
    virtual ~Minigunner();


	virtual void draw();

	void update(float frameTime);
	virtual const D3DXVECTOR2 getVelocity() const { return velocity; }
	virtual void  setVelocity(D3DXVECTOR2 v) { velocity = v; }
	void setX(float newX) { this->x = newX; }
	void setY(float newY) { this->y = newY; }

	
};



