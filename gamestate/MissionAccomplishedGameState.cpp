#include "MissionAccomplishedGameState.h"

#include "../graphics.h"
#include "../Game.h"
#include "../Minigunner.h"
#include "../MissionAccomplishedMessage.h"

MissionAccomplishedGameState::MissionAccomplishedGameState(Game & game) : GameState(game) {
	gameOverMessage = new MissionAccomplishedMessage(game);
	Minigunner * minigunner1 = game.GetGDIMinigunner();
	if (minigunner1 != NULL) {
		minigunner1->SetAnimate(false);
	}

	Minigunner * enemyMinigunner1 = game.GetNODMinigunner();
	if (enemyMinigunner1 != NULL) {
		enemyMinigunner1->SetAnimate(false);
	}
}


GameState * MissionAccomplishedGameState::Update(float frameTime) {


	Graphics * graphics = game.GetGraphics();
	graphics->BeginScene(graphicsNS::CUSTOM6);
	this->Render();
	graphics->endScene();
	graphics->ShowBackbuffer();

	GameState * nextGameState = game.ProcessGameEvents();
	if(nextGameState != nullptr) {
		return nextGameState;
	}
	else {
		return this;
	}

}


void MissionAccomplishedGameState::Render() {
	//Consider how to  handle if we want GameOver to draw different background color
	//	Does rendering and everything go in Render?
	//	Do we just have one Update method, that includes render
	//	And maybe GameState has base functions that can be called to begin and end scene
	Minigunner * minigunner1 = game.GetGDIMinigunner();
	if (minigunner1 != nullptr) {
		minigunner1->Draw();
	}

	Minigunner * enemyMinigunner1 = game.GetNODMinigunner();
	if (enemyMinigunner1 != nullptr) {
		if (enemyMinigunner1->GetHealth() > 0) {
			enemyMinigunner1->Draw();
		}
	}

	gameOverMessage->Draw();


}



std::string MissionAccomplishedGameState::GetName()
{
	return "Game Over";
}