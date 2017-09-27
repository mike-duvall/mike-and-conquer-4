#pragma once

#include "AsyncGameEvent.h"

class CreateNODMinigunnerGameEvent : public AsyncGameEvent {

public:
	CreateNODMinigunnerGameEvent(Game * aGame, int anX, int aY);

protected:
	GameState * ProcessImpl() override;

private:
	int x;
	int y;

};
