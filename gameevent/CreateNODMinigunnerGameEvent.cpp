#include "CreateNODMinigunnerGameEvent.h"

#include "../game.h"

CreateNODMinigunnerGameEvent::CreateNODMinigunnerGameEvent(Game * aGame, int anX, int aY) : AsyncGameEvent(aGame) {
	this->x = anX;
	this->y = aY;
}


Minigunner * CreateNODMinigunnerGameEvent::GetMinigunner() {
	return static_cast<Minigunner *>(GetResult());
}


GameState * CreateNODMinigunnerGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	result = game->InitializeNODMinigunner(x, y);
	return newGameState;
}
