#include "GetAllGDIMinigunnersGameEvent.h"

#include "../game.h"


GetAllGDIMinigunnersGameEvent::GetAllGDIMinigunnersGameEvent(Game * aGame) : NewGameEvent(aGame) {
}



std::vector<Minigunner * > * GetAllGDIMinigunnersGameEvent::GetAllGdiMinigunners() {
	return (std::vector<Minigunner * > *) GetResult();
}

GameState * GetAllGDIMinigunnersGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	result = game->GetGDIMinigunners();
	return newGameState;
}