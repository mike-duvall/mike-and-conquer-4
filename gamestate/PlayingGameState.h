#pragma once

#include "GameState.h"


class Input;

class PlayingGameState : public GameState {

public:
	PlayingGameState(Game & game);
	void HandleLeftMouseDown(Input * input);
	virtual GameState * Update(float frameTime);
	bool MinigunnersExistAndAreAllDead();
	virtual void Render();
	virtual std::string PlayingGameState::GetName();

private:
	bool CheckForAndHandleLeftClickOnFriendlyUnit(Input * input);
	bool CheckForAndHandleLeftClickOnMap(Input * input);
	bool CheckForAndHandleLeftClickOnEnemyUnit(Input * input);
};
