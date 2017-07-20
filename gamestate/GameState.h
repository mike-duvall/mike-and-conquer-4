#pragma once


class Game;

#include <string>

class GameState {
public:
	GameState(Game & game);
	virtual GameState *  Update(float frameTime) = 0;
	virtual void Render() = 0;
	virtual std::string GetName() = 0;

protected:
	Game & game;
};