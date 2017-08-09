#pragma once

#include "GameState.h"


class PlayingGameState : public GameState {

public:
	PlayingGameState(Game & game);
	virtual GameState * Update(float frameTime);
	bool MinigunnersExistAndAreAllDead();
	virtual void Render();
	virtual std::string PlayingGameState::GetName();

};
