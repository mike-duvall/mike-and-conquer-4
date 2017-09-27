#pragma once


#include "AsyncGameEvent.h"


class Minigunner;
class Game;


class GetGDIMinigunnerByIdGameEvent : public AsyncGameEvent {

public:
	GetGDIMinigunnerByIdGameEvent(Game * aGame, int id);
	Minigunner * GetMinigunner();

protected:
	GameState * ProcessImpl() override;

private:
	int id;


};