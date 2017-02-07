#include "CreateNODMinigunnerGameEvent.h"

#include "game.h"

CreateNODMinigunnerGameEvent::CreateNODMinigunnerGameEvent(Game * aGame, int anX, int aY) : GameEvent(aGame) {
	this->x = anX;
	this->y = aY;
}


void CreateNODMinigunnerGameEvent::CreateNODMinigunnerGameEvent::Process() {
	game->InitializeNODMinigunner(x, y);
}
