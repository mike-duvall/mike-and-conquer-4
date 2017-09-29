#pragma once

#include "AsyncGameEvent.h"


class Minigunner;

class CreateNODMinigunnerGameEvent : public AsyncGameEvent {

public:
	CreateNODMinigunnerGameEvent(Game * aGame, int anX, int aY);
	Minigunner * GetMinigunner();

protected:
	GameState * ProcessImpl() override;

private:
	int x;
	int y;

};
