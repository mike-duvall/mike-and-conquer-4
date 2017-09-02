#pragma once



#pragma once

#include "GameEvent.h"

#include <mutex>

class Minigunner;
class Game;


class GetMinigunnerAtLocationGameEvent : public GameEvent {

public:
	GetMinigunnerAtLocationGameEvent(Game * aGame, int x, int y);
	Minigunner * GetMinigunner();
	virtual GameState * Process();

private:
	std::condition_variable condition;

	int x;
	int y;


};