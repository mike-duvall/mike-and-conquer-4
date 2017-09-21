#include "PlayingGameState.h"

#include "../Game.h"
#include "../gameobject/Minigunner.h"
#include "../gameobject/Circle.h"
#include "../util/ShpImageExplorer.h"
#include "MissionAccomplishedGameState.h"
#include "MissionFailedGameState.h"


PlayingGameState::PlayingGameState(Game & game)  : GameState(game) {

}


void PlayingGameState::HandleLeftMouseDown(Input * input) {

	bool handledEvent = CheckForAndHandleLeftClickOnFriendlyUnit(input);
	if (!handledEvent) {
		handledEvent = 	CheckForAndHandleLeftClickOnEnemyUnit(input);
	}
	if (!handledEvent) {
		CheckForAndHandleLeftClickOnMap(input);
	}
	
}

GameState * PlayingGameState::Update(float frameTime) {

	game.ProcessGameEvents();


	Input * input = game.GetInput();
	if (input->isLeftMouseDown()) {
		HandleLeftMouseDown(input);
	}

	std::vector<Minigunner * > * gdiMinigunners = game.GetGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		nextMinigunner->Update(frameTime);
	}

	Minigunner * enemyMinigunner1 = game.GetNODMinigunner();
	if (enemyMinigunner1 != NULL) {
		enemyMinigunner1->Update(frameTime);
	}


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



	if (enemyMinigunner1 != nullptr && enemyMinigunner1->GetHealth() <= 0) {
		return new MissionAccomplishedGameState(game);
	}
	else if(MinigunnersExistAndAreAllDead()) {
		return new MissionFailedGameState(game);
	}
	else {
		return this;
	}

	return this;

}

bool PlayingGameState::MinigunnersExistAndAreAllDead()
{
	std::vector<Minigunner * > * gdiMinigunners = game.GetGDIMinigunners();
	if(gdiMinigunners->size() == 0) {
		return false;
	}

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if(nextMinigunner->GetHealth() > 0) {
			return false;
		}
	}

	return true;
}



void PlayingGameState::Render() {

	std::vector<Minigunner * > * gdiMinigunners = game.GetGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		nextMinigunner->Draw();
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

bool PlayingGameState::CheckForAndHandleLeftClickOnFriendlyUnit(Input * input) {
	int mouseX = input->getMouseX();
	int mouseY = input->getMouseY();

	std::vector<Minigunner * > * gdiMinigunners = game.GetGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->PointIsWithin(mouseX, mouseY)) {
			game.SelectSingleGDIUnit(nextMinigunner);
			return true;
		}
	}

	return false;
}

bool PlayingGameState::CheckForAndHandleLeftClickOnMap(Input * input) {
	int mouseX = input->getMouseX();
	int mouseY = input->getMouseY();

	std::vector<Minigunner * > * gdiMinigunners = game.GetGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->GetIsSelected()) {
			nextMinigunner->OrderToMoveToDestination(mouseX, mouseY);
		}
	}

	return true;

}

bool PlayingGameState::CheckForAndHandleLeftClickOnEnemyUnit(Input * input) {
	int mouseX = input->getMouseX();
	int mouseY = input->getMouseY();


	Minigunner * enemyMinigunner = game.GetNODMinigunner();
	if (enemyMinigunner != nullptr && enemyMinigunner->PointIsWithin(mouseX, mouseY)) {
		std::vector<Minigunner * > * gdiMinigunners = game.GetGDIMinigunners();

		std::vector<Minigunner *>::iterator iter;
		for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
			Minigunner * nextMinigunner = *iter;
			if (nextMinigunner->GetIsSelected()) {
				nextMinigunner->OrderToMoveToAttackEnemyUnit(enemyMinigunner);
			}
		}

		return true;

	}

	return false;
}

std::string PlayingGameState::GetName()
{
	return "Playing";
}