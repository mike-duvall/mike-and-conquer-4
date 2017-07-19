#pragma once


#include "GameEvent.h"

#include <mutex>

class Minigunner;
class Game;


class ResetGameGameEvent : public GameEvent {

public:
	ResetGameGameEvent(Game * aGame);
	virtual GameState *  Process();

private:
	std::condition_variable condition;


};
