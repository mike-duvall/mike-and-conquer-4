#include "GameEvent.h"


#include "game.h"

GameEvent::GameEvent(Game * aGame, const std::string & type, int x, int y) {
	this->game = aGame;
	this->eventType = type;
	this->x = x;
	this->y = y;
}



void GameEvent::Process() {
	game->InitializeGDIMinigunner(x, y);
}
