#pragma once

#include "GameState.h"


class GameOverMessage;

class GameOverGameState : public GameState {


public:
	GameOverGameState(Game & game);
	virtual GameState * Update(float frameTime);
	virtual void Render();
	virtual std::string GetName();


private:

	GameOverMessage * gameOverMessage;
};