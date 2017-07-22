#pragma once

#include "GameEvent.h"

class CreateNODMinigunnerGameEvent : public GameEvent {

public:
	CreateNODMinigunnerGameEvent(Game * aGame, int anX, int aY);
	virtual GameState * Process();

private:
	int x;
	int y;

};
