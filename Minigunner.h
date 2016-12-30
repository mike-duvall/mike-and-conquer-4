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


class Minigunner
{

  public:

	Minigunner(Game * game, Graphics * graphics, int x, int y, UnitSelectCursor * unitSelectionCursor, Input * input, bool isEnemy);
    virtual ~Minigunner();


	virtual void draw();

	void update(float frameTime);
	virtual const D3DXVECTOR2 getVelocity() const { return velocity; }
	virtual void  setVelocity(D3DXVECTOR2 v) { velocity = v; }
	void setX(float newX) { this->x = newX; }
	void setY(float newY) { this->y = newY; }
	int getX() { return this->x; }
	int getY() { return this->y; }
	bool pointIsWithin(int x, int y);
	void setSelected(bool selected) { this->isSelected = selected; }
	bool getIsSelected() { return this->isSelected; }
	void MoveTo(int x, int y);
	int getHealth() { return this->health; }

private:

	Graphics * graphics;
	GameSprite * gameSprite;
	UnitSelectCursor * unitSelectCursor;
	Input * input;
	Game * game;

	const int   WIDTH = 16;                // image width
	const int   HEIGHT = 16;               // image height

	float       x;
	float       y;
	UINT         width;
	UINT         height;
	D3DXVECTOR2 velocity;

	bool    initialized;
	bool isSelected;

	int destinationX;
	int destinationY;

	bool isEnemy;

	std::string state;
	void handleIdleState(float frameTime);
	void handleMovingState(float frameTime);
	void handleAttackingState(float frameTime);

	bool isInAttackRange();
	void moveTowardsDestination(float frameTime);
	int calculateDistanceToTarget();

	int health;

	void reduceHealth(int amount);
	Minigunner * enemyAttacking;

};



