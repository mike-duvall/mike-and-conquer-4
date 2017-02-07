#pragma once




#include "GameEvent.h"



class CreateNODMinigunnerGameEvent : public GameEvent {

public:
	CreateNODMinigunnerGameEvent(Game * aGame, int anX, int aY);
	virtual void Process();

private:
	int x;
	int y;

};
