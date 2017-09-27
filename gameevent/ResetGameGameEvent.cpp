#include "ResetGameGameEvent.h"

#include "../game.h"

ResetGameGameEvent::ResetGameGameEvent(Game * aGame) : AsyncGameEvent(aGame) {
}


GameState * ResetGameGameEvent::ProcessImpl() {
	return game->ResetGame();
}
