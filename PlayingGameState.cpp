#include "PlayingGameState.h"

#include "Game.h"
#include "Minigunner.h"
#include "Circle.h"
#include "ShpImageExplorer.h"



PlayingGameState::PlayingGameState(Game & game)  : GameState(game) {

}


void PlayingGameState::Update(float frameTime) {

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