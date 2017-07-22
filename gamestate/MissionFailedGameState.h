#pragma once

#include "GameState.h"

class MissionFailedMessage;

class MissionFailedGameState : public GameState {


public:
	MissionFailedGameState(Game & game);
	virtual GameState * Update(float frameTime);
	virtual void Render();
	virtual std::string GetName();


private:

	MissionFailedMessage * gameOverMessage;
};