#include "CreateGDIMinigunnerGameEvent.h"
#include "../game.h"


CreateGDIMinigunnerGameEvent::CreateGDIMinigunnerGameEvent(Game * aGame, int anX, int aY) : GameEvent(aGame) {
	createdMinigunner = nullptr;
	this->x = anX;
	this->y = aY;
}


Minigunner * CreateGDIMinigunnerGameEvent::GetMinigunner() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);

	return createdMinigunner;
}


GameState * CreateGDIMinigunnerGameEvent::Process() {
	GameState * newGameState = nullptr;
	createdMinigunner = game->InitializeGDIMinigunner(x, y);
	condition.notify_one();
	return newGameState;
}