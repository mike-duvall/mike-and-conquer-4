#pragma once

#include <string>

class Game;

class GameEvent {
	public:

		GameEvent(Game * aGame, const std::string & type, int x, int y);
		virtual void Process();

		std::string eventType;
		int x;
		int y;

protected:
		Game * game;
};