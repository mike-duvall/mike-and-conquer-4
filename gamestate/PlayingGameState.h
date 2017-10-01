#pragma once

#include "GameState.h"
#include "../gameobject/Minigunner.h"
#include <vector>


class Input;

class PlayingGameState : public GameState {

	// TODO  Review what needs to be public
public:
	PlayingGameState(Game & game);
	void HandleLeftMouseDown(Input * input);
	void UpdateMinigunners(float frameTime, std::vector<Minigunner*>* minigunners);

	GameState * Update(float frameTime) override;
	bool NodMinigunnersExistAndAreAllDead();
	bool GdiMinigunnersExistAndAreAllDead();
	void DrawMinigunners(std::vector<Minigunner*>* minigunners);
	void DrawGdiMinigunners();
	void DrawNodMinigunners();
	virtual void Render();
	virtual std::string PlayingGameState::GetName();

private:

	void UpdateGdiMinigunners(float frameTime);
	void UpdateNodMinigunners(float frameTime);
	bool CheckForAndHandleLeftClickOnFriendlyUnit(Input * input);
	bool CheckForAndHandleLeftClickOnMap(Input * input);
	bool CheckForAndHandleLeftClickOnEnemyUnit(Input * input);
};
