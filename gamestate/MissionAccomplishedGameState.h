#pragma once

#include "GameState.h"


class MissionAccomplishedMessage;

class MissionAccomplishedGameState : public GameState {


public:
	MissionAccomplishedGameState(Game & game);
	virtual GameState * Update(float frameTime);
	virtual void Render();
	virtual std::string GetName();


private:

	MissionAccomplishedMessage * gameOverMessage;
};