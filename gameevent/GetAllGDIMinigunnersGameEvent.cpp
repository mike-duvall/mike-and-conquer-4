#include "GetAllGDIMinigunnersGameEvent.h"

#include "../game.h"


GetAllGDIMinigunnersGameEvent::GetAllGDIMinigunnersGameEvent(Game * aGame) : AsyncGameEvent(aGame) {
}



std::vector<Minigunner * > * GetAllGDIMinigunnersGameEvent::GetAllGdiMinigunners() {
	return static_cast<std::vector<Minigunner *> *>(GetResult());
}

GameState * GetAllGDIMinigunnersGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	result = game->GetGDIMinigunners();
	return newGameState;
}