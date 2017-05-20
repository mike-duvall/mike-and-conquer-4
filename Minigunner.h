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



class Minigunner
{

  public:

	Minigunner(Game * game, Graphics * graphics, int x, int y, UnitSelectCursor * unitSelectionCursor, Input * input, bool isEnemy);
    virtual ~Minigunner();


	virtual void Draw();

	void Update(float frameTime);
	virtual const D3DXVECTOR2 GetVelocity() const { return velocity; }
	virtual void  SetVelocity(D3DXVECTOR2 v) { velocity = v; }
	void SetX(float newX) { this->x = newX; }
	void SetY(float newY) { this->y = newY; }
	int GetX() { return (int)this->x; }
	int GetY() { return (int)this->y; }
	bool PointIsWithin(int x, int y);
	void SetSelected(bool selected) { this->isSelected = selected; }
	bool GetIsSelected() { return this->isSelected; }
	void MoveTo(int x, int y);
	int GetHealth() { return this->health; }

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

	int health;

	Minigunner * currentAttackTarget;

	MikeRectangle * shpBoundingRectangle;
	boolean drawShpBoundingRectangle;


	std::string state;

	void HandleIdleState(float frameTime);
	void HandleMovingState(float frameTime);
	void HandleAttackingState(float frameTime);

	bool IsInAttackRange();
	void MoveTowardsDestination(float frameTime);
	int CalculateDistanceToTarget();
	void ReduceHealth(int amount);

};



