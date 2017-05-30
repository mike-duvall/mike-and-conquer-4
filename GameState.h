#pragma once


class Game;

class GameState {
public:
	GameState(Game & game);
	virtual void Update(float frameTime);

private:
	Game & game;
};