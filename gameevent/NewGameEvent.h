#pragma once



class Game;
class GameState;

#include "GameEvent.h"
#include <mutex>

class NewGameEvent  {
public:

	NewGameEvent(Game * aGame);
	virtual ~NewGameEvent() = default;

	GameState * Process();
	void * GetResult();

protected:

	virtual GameState * ProcessImpl() = 0;
	void * result;
	Game * game;

private:
	std::condition_variable condition;


};

