#include "PlayingGameState.h"

#include "../Game.h"
#include "../gameobject/Minigunner.h"
#include "../gameobject/Circle.h"
#include "../util/ShpImageExplorer.h"
#include "MissionAccomplishedGameState.h"
#include "MissionFailedGameState.h"



PlayingGameState::PlayingGameState(Game & game)  : GameState(game) {

}


GameState * PlayingGameState::Update(float frameTime) {

	game.ProcessGameEvents();
	Minigunner * minigunner1 = game.GetGDIMinigunner();
	if (minigunner1 != NULL) {
		minigunner1->Update(frameTime);
	}

	Minigunner * enemyMinigunner1 = game.GetNODMinigunner();
	if (enemyMinigunner1 != NULL) {
		enemyMinigunner1->Update(frameTime);
	}

	Input * input = game.GetInput();

	Circle * circle = game.GetCircle();
	if (input->isLeftMouseDown()) {
		circle->SetX(input->getMouseX());
		circle->SetY(input->getMouseY());
	}

	ShpImageExplorer * shpImageExplorer = game.GetShpImageExplorer();
	if (shpImageExplorer != NULL) {
		shpImageExplorer->Update(frameTime);
	}


	Graphics * graphics = game.GetGraphics();
	graphics->BeginScene(graphicsNS::CUSTOM6);
	this->Render();
	graphics->endScene();
	graphics->ShowBackbuffer();



	if (enemyMinigunner1 != NULL && enemyMinigunner1->GetHealth() <= 0) {
		return new MissionAccomplishedGameState(game);
	}
	else if(minigunner1 != NULL && minigunner1->GetHealth() <= 0) {
		return new MissionFailedGameState(game);
	}
	else {
		return this;
	}


	return this;

}



void PlayingGameState::Render() {

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

	ShpImageExplorer * shpImageExplorer = game.GetShpImageExplorer();
	if (shpImageExplorer != NULL) {
		shpImageExplorer->Draw();
	}

	Circle * circle = game.GetCircle();
	Graphics * graphics = game.GetGraphics();
	circle->Draw(graphics->Get3Ddevice());

}

std::string PlayingGameState::GetName()
{
	return "Playing";
}