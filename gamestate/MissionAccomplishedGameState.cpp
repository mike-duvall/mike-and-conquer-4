#include "MissionAccomplishedGameState.h"

#include "../graphics.h"
#include "../Game.h"
#include "../gameobject/Minigunner.h"
#include "../gameobject/MissionAccomplishedMessage.h"

MissionAccomplishedGameState::MissionAccomplishedGameState(Game & game) : GameState(game) {
	gameOverMessage = new MissionAccomplishedMessage(game);

	std::vector<Minigunner * > gdiMinigunners = game.getGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners.begin(); iter != gdiMinigunners.end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		nextMinigunner->Draw();
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
	std::vector<Minigunner * > gdiMinigunners = game.getGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners.begin(); iter != gdiMinigunners.end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		nextMinigunner->Draw();
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