#pragma once


#include "NewGameEvent.h"


class Minigunner;
class Game;


class GetGDIMinigunnerByIdGameEvent : public NewGameEvent {

public:
	GetGDIMinigunnerByIdGameEvent(Game * aGame, int id);
	Minigunner * GetMinigunner();

protected:
	GameState * ProcessImpl() override;

private:
	int id;


};