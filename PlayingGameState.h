#pragma once

#include "GameState.h"




class PlayingGameState : public GameState {


public:
	PlayingGameState(Game & game);
	virtual void Update(float frameTime);
	virtual void Render();
};
