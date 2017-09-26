#pragma once

#include "NewGameEvent.h"


class Minigunner;
class Game;


class GetNODMinigunnerGameEvent : public NewGameEvent {

public:
	GetNODMinigunnerGameEvent(Game * aGame);
	Minigunner * GetMinigunner();

protected:
	GameState * ProcessImpl() override;


}; 
