#pragma once

#include "GameEvent.h"

#include <mutex>

class Minigunner;
class Game;

class CreateGDIMinigunnerGameEvent : public GameEvent {

public:
	CreateGDIMinigunnerGameEvent(Game * aGame, int anX, int aY);
	Minigunner * GetMinigunner();
	virtual GameState * Process();

private:
	std::condition_variable condition;
	int x;
	int y;
	Minigunner * createdMinigunner;

};
