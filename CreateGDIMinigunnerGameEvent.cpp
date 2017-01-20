#include "CreateGDIMinigunnerGameEvent.h"

#include "game.h"

CreateGDIMinigunnerGameEvent::CreateGDIMinigunnerGameEvent(Game * aGame, int anX, int aY) : GameEvent(aGame) {
	this->x = anX;
	this->y = aY;
}


void CreateGDIMinigunnerGameEvent::CreateGDIMinigunnerGameEvent::Process() {
	game->InitializeGDIMinigunner(x, y);
}
