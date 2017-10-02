#pragma once


#include "AsyncGameEvent.h"


class Minigunner;
class Game;


class GetNodMinigunnerAtLocationGameEvent : public AsyncGameEvent {

public:
	GetNodMinigunnerAtLocationGameEvent(Game * aGame, int x, int y);
	Minigunner * GetMinigunner();


protected:
	GameState * ProcessImpl() override;


private:
	int x;
	int y;

};
