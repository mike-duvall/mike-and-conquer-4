#include "CreateNODMinigunnerGameEvent.h"

#include "../game.h"

CreateNODMinigunnerGameEvent::CreateNODMinigunnerGameEvent(Game * aGame, int anX, int aY) : GameEvent(aGame) {
	this->x = anX;
	this->y = aY;
}


GameState * CreateNODMinigunnerGameEvent::CreateNODMinigunnerGameEvent::Process() {
	GameState * newGameState = nullptr;
	game->InitializeNODMinigunner(x, y);
	return newGameState;
}
