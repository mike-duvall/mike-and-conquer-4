#include "GetAllGDIMinigunnersGameEvent.h"

#include "../game.h"


GetAllGDIMinigunnersGameEvent::GetAllGDIMinigunnersGameEvent(Game * aGame) : NewGameEvent(aGame) {
}





std::vector<Minigunner * > * GetAllGDIMinigunnersGameEvent::GetAllGDIMinigunners() {
//	std::mutex dummyMutex;
//	std::unique_lock<std::mutex> locker(dummyMutex);
//	condition.wait(locker);
//	return foundMinigunners;
	return (std::vector<Minigunner * > *) GetResult();
}

GameState * GetAllGDIMinigunnersGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	result = game->GetGDIMinigunners();
	return newGameState;
}