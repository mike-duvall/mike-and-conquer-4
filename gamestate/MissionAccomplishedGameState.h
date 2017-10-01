#pragma once

#include "GameState.h"
#include "../gameobject/Minigunner.h"
#include <vector>

class MissionAccomplishedMessage;

class MissionAccomplishedGameState : public GameState {


public:
	MissionAccomplishedGameState(Game & game);
	void TurnOffMinigunnerAnimate(std::vector<Minigunner*>* mnigunners);
	void TurnOffGdiAnimate();
	void TurnOffNodAnimate();
	virtual GameState * Update(float frameTime);
	void DrawMinigunners(std::vector<Minigunner*>* minigunners);
	void DrawGdiMinigunners();
	void DrawNodMinigunners();
	virtual void Render();
	virtual std::string GetName();


private:

	MissionAccomplishedMessage * gameOverMessage;
};