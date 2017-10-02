#pragma once


#include "AsyncGameEvent.h"


class Minigunner;
class Game;


class GetNodMinigunnerByIdGameEvent : public AsyncGameEvent {

public:
	GetNodMinigunnerByIdGameEvent(Game * aGame, int id);
	Minigunner * GetMinigunner();

protected:
	GameState * ProcessImpl() override;

private:
	int id;


};