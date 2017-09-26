#pragma once



class Game;
class GameState;

#include "GameEvent.h"
#include <mutex>

class NewGameEvent : public GameEvent {
public:

	NewGameEvent(Game * aGame);
	virtual ~NewGameEvent() = default;

	GameState * Process() override;
	void * GetResult();

protected:

	virtual GameState * ProcessImpl() = 0;
	void * result;

private:
	std::condition_variable condition;


};

