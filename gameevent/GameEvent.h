#pragma once

class Game;
class GameState;

class GameEvent {
	public:

		GameEvent(Game * aGame);
		virtual GameState * Process() = 0;

		 
protected:
		Game * game;
};

