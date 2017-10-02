#include "GetAllNodMinigunnersGameEvent.h"

#include "../game.h"


GetAllNodMinigunnersGameEvent::GetAllNodMinigunnersGameEvent(Game * aGame) : AsyncGameEvent(aGame) {
}



std::vector<Minigunner * > * GetAllNodMinigunnersGameEvent::GetAllNodMinigunners() {
	return static_cast<std::vector<Minigunner *> *>(GetResult());
}

GameState * GetAllNodMinigunnersGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	result = game->GetNodMinigunners();
	return newGameState;
}