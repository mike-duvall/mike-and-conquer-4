#pragma once



class Game;
class GameState;

#include <mutex>

class AsyncGameEvent  {
public:

	AsyncGameEvent(Game * aGame);
	virtual ~AsyncGameEvent() = default;

	GameState * Process();
	void * GetResult();

protected:

	virtual GameState * ProcessImpl() = 0;
	void * result;
	Game * game;

private:
	std::condition_variable condition;


};

