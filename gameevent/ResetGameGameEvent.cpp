#include "ResetGameGameEvent.h"

#include "../game.h"

ResetGameGameEvent::ResetGameGameEvent(Game * aGame) : NewGameEvent(aGame) {
}


GameState * ResetGameGameEvent::ProcessImpl() {
	return game->ResetGame();
}
