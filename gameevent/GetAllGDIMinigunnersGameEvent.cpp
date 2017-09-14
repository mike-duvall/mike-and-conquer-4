#include "GetAllGDIMinigunnersGameEvent.h"

#include "../game.h"


GetAllGDIMinigunnersGameEvent::GetAllGDIMinigunnersGameEvent(Game * aGame) : GameEvent(aGame) {
}





std::vector<Minigunner * > * GetAllGDIMinigunnersGameEvent::GetAllGDIMinigunners() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);
	return foundMinigunners;
}

GameState * GetAllGDIMinigunnersGameEvent::Process() {
	GameState * newGameState = nullptr;
	foundMinigunners = game->getGDIMinigunners();

	condition.notify_one();
	return newGameState;
}