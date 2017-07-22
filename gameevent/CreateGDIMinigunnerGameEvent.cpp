
#include "../game.h"
#include "CreateGDIMinigunnerGameEvent.h"


CreateGDIMinigunnerGameEvent::CreateGDIMinigunnerGameEvent(Game * aGame, int anX, int aY) : GameEvent(aGame) {
	this->x = anX;
	this->y = aY;
}


GameState * CreateGDIMinigunnerGameEvent::CreateGDIMinigunnerGameEvent::Process() {
	GameState * newGameState = nullptr;
	game->InitializeGDIMinigunner(x, y);
	return newGameState;
}
