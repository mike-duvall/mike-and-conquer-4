#pragma once

#include "NewGameEvent.h"


class Minigunner;
class Game;

class CreateGDIMinigunnerGameEvent : public NewGameEvent {

public:
	CreateGDIMinigunnerGameEvent(Game * aGame, int anX, int aY);
	Minigunner * GetMinigunner();

protected:
	GameState * ProcessImpl() override;

private:
	int x;
	int y;

};
