#pragma once

#include "AsyncGameEvent.h"


class Minigunner;
class Game;


class ResetGameGameEvent : public AsyncGameEvent {

public:
	ResetGameGameEvent(Game * aGame);

protected:
	GameState *  ProcessImpl() override;



};
