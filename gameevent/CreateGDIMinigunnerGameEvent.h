#pragma once

#include "AsyncGameEvent.h"


class Minigunner;
class Game;

class CreateGDIMinigunnerGameEvent : public AsyncGameEvent {

public:
	CreateGDIMinigunnerGameEvent(Game * aGame, int anX, int aY);
	Minigunner * GetMinigunner();

protected:
	GameState * ProcessImpl() override;

private:
	int x;
	int y;

};
