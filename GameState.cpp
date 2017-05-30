#include "GameState.h"

#include "Game.h"
#include "Minigunner.h"
#include "Circle.h"
#include "ShpImageExplorer.h"


GameState::GameState(Game & aGame) : game(aGame) {
}

void GameState::Update(float frameTime) {

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