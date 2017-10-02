#pragma once


#include "AsyncGameEvent.h"


class Minigunner;
class Game;


class GetGdiMinigunnerAtLocationGameEvent : public AsyncGameEvent {

public:
	GetGdiMinigunnerAtLocationGameEvent(Game * aGame, int x, int y);
	Minigunner * GetMinigunner();


protected:
	GameState * ProcessImpl() override;


private:
	int x;
	int y;

};