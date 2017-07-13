#include "MissionFailedGameState.h"

#include "graphics.h"
#include "Game.h"
#include "Minigunner.h"
#include "MissionFailedMessage.h"

MissionFailedGameState::MissionFailedGameState(Game & game) : GameState(game) {
	gameOverMessage = new MissionFailedMessage(game);
	Minigunner * minigunner1 = game.GetGDIMinigunner();
	if (minigunner1 != NULL) {
		minigunner1->SetAnimate(false);
	}

	Minigunner * enemyMinigunner1 = game.GetNODMinigunner();
	if (enemyMinigunner1 != NULL) {
		enemyMinigunner1->SetAnimate(false);
	}
}


GameState * MissionFailedGameState::Update(float frameTime) {

	game.ProcessGameEvents();
	Graphics * graphics = game.GetGraphics();
	graphics->BeginScene(graphicsNS::CUSTOM6);
	this->Render();
	graphics->endScene();
	graphics->ShowBackbuffer();

	return this;


}


void MissionFailedGameState::Render() {
	//Consider how to  handle if we want GameOver to draw different background color
	//	Does rendering and everything go in Render?
	//	Do we just have one Update method, that includes render
	//	And maybe GameState has base functions that can be called to begin and end scene
	Minigunner * minigunner1 = game.GetGDIMinigunner();
	if (minigunner1 != NULL) {
		minigunner1->Draw();
	}

	Minigunner * enemyMinigunner1 = game.GetNODMinigunner();
	if (enemyMinigunner1 != NULL) {
		if (enemyMinigunner1->GetHealth() > 0) {
			enemyMinigunner1->Draw();
		}
	}

	gameOverMessage->Draw();


}



std::string MissionFailedGameState::GetName()
{
	return "Mission Failed";
}