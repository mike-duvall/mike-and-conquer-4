#pragma once

#include "../graphics.h"

class Graphics;
class Game;
class GameSprite;
class UnitSelectCursor;
class Input;
class Game;
class MikeRectangle;
class ShpFileColorMapper;


class Minigunner
{

  public:

	Minigunner(Game * game, int x, int y, UnitSelectCursor * unitSelectionCursor, Input * input, bool isEnemy, ShpFileColorMapper * shpFileColorMapper);
    virtual ~Minigunner();


	virtual void Draw();

	void Update(float frameTime);
	virtual const D3DXVECTOR2 GetVelocity() const { return velocity; }
	virtual void  SetVelocity(D3DXVECTOR2 v) { velocity = v; }
	void SetX(int newX) { this->x = newX; }
	void SetY(int newY) { this->y = newY; }
	int GetX() { return this->x; }
	int GetY() { return this->y; }
	bool PointIsWithin(int x, int y);
	void SetSelected(bool selected) { this->isSelected = selected; }
	bool GetIsSelected() { return this->isSelected; }
	void SetDestination(int x, int y);
	int GetHealth() { return this->health; }
	void SetAnimate(bool newValue);



private:

	Graphics * graphics;
	GameSprite * gameSprite;
	UnitSelectCursor * unitSelectCursor;
	Input * input;
	Game * game;


	const int   WIDTH = 16;                // image width
	const int   HEIGHT = 16;               // image height

	int	x;
	int	y;
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



	enum AnimationSequences { STANDING_STILL, WALKING_UP, SHOOTING_UP };

	std::string state;

	void HandleIdleState(float frameTime);
	void HandleMovingState(float frameTime);
	void HandleAttackingState(float frameTime);
	Minigunner* FindFirstGdiMinigunner();

	bool IsInAttackRange();
	bool IsAtDestination();
	void MoveTowardsDestination(float frameTime);
	int CalculateDistanceToTarget();
	void ReduceHealth(int amount);

	void HandleEnemyUpdate(float frameTime);

	boolean enemyStateIsSleeping;
	int enemySleepCountdownTimer;

};



