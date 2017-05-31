#pragma once


class Game;

class GameState {
public:
	GameState(Game & game);
	virtual void Update(float frameTime) = 0;
	virtual void Render() = 0;

protected:
	Game & game;
};