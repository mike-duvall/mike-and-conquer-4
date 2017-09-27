#include "CreateGDIMinigunnerGameEvent.h"
#include "../game.h"


CreateGDIMinigunnerGameEvent::CreateGDIMinigunnerGameEvent(Game * aGame, int anX, int aY) : AsyncGameEvent(aGame) {
	this->x = anX;
	this->y = aY;
}


Minigunner * CreateGDIMinigunnerGameEvent::GetMinigunner() {
	return static_cast<Minigunner *>(GetResult());
}



GameState * CreateGDIMinigunnerGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	result = game->InitializeGDIMinigunner(x, y);
	return newGameState;
}
