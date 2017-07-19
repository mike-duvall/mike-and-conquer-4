#include "ResetGameGameEvent.h"

#include "game.h"

ResetGameGameEvent::ResetGameGameEvent(Game * aGame) : GameEvent(aGame) {
}


GameState * ResetGameGameEvent::Process() {
	return game->ResetGame();
}
