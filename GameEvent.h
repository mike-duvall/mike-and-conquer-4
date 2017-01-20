#pragma once

#include <string>

class Game;

class GameEvent {
	public:

		GameEvent(Game * aGame);
		virtual void Process() = 0;


protected:
		Game * game;
};