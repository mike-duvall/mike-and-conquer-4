#pragma once

#include "GameState.h"




class PlayingGameState : public GameState {

public:
	PlayingGameState(Game & game);
	virtual GameState * Update(float frameTime);
	virtual void Render();

};
