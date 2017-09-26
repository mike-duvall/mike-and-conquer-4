#pragma once

#include "NewGameEvent.h"

class CreateNODMinigunnerGameEvent : public NewGameEvent {

public:
	CreateNODMinigunnerGameEvent(Game * aGame, int anX, int aY);

protected:
	GameState * ProcessImpl() override;

private:
	int x;
	int y;

};
