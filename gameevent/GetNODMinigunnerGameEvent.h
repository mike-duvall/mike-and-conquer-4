#pragma once

#include "AsyncGameEvent.h"


class Minigunner;
class Game;


class GetNODMinigunnerGameEvent : public AsyncGameEvent {

public:
	GetNODMinigunnerGameEvent(Game * aGame);
	Minigunner * GetMinigunner();

protected:
	GameState * ProcessImpl() override;


}; 
