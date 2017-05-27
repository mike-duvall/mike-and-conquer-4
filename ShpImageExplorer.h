#pragma once



#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "graphics.h"

class Graphics;
class Game;
class GameSprite;
class UnitSelectCursor;
class Input;
class Game;
class MikeRectangle;
class AnimationSequence;



class ShpImageExplorer
{

public:

	ShpImageExplorer(Game * game, int x, int y, Input * input);

	virtual void Draw();

	void Update(float frameTime);
	void SetX(int newX) { this->x = newX; }
	void SetY(int newY) { this->y = newY; }
	int GetX() { return this->x; }
	int GetY() { return this->y; }
	void IncrementFrame();
	void DecrementFrame();


private:

	Graphics * graphics;
	GameSprite * gameSprite;
	Input * input;
	Game * game;

	unsigned int currentImageIndex;
	AnimationSequence * animationSequence;


	int	x;
	int	y;
	UINT         width;
	UINT         height;

	bool    initialized;


	MikeRectangle * shpBoundingRectangle;
	boolean drawShpBoundingRectangle;


};



