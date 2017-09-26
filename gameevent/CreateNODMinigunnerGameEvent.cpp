#include "CreateNODMinigunnerGameEvent.h"

#include "../game.h"

CreateNODMinigunnerGameEvent::CreateNODMinigunnerGameEvent(Game * aGame, int anX, int aY) : NewGameEvent(aGame) {
	this->x = anX;
	this->y = aY;
}


GameState * CreateNODMinigunnerGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	game->InitializeNODMinigunner(x, y);
	return newGameState;
}
