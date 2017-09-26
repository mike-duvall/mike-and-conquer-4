#pragma once

#include "NewGameEvent.h"


class Minigunner;
class Game;


class ResetGameGameEvent : public NewGameEvent {

public:
	ResetGameGameEvent(Game * aGame);

protected:
	GameState *  ProcessImpl() override;



};
