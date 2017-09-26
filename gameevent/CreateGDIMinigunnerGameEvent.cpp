#include "CreateGDIMinigunnerGameEvent.h"
#include "../game.h"


CreateGDIMinigunnerGameEvent::CreateGDIMinigunnerGameEvent(Game * aGame, int anX, int aY) : NewGameEvent(aGame) {
	this->x = anX;
	this->y = aY;
}


Minigunner * CreateGDIMinigunnerGameEvent::GetMinigunner() {
	return (Minigunner *) GetResult();
}



GameState * CreateGDIMinigunnerGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	result = game->InitializeGDIMinigunner(x, y);
	return newGameState;
}
