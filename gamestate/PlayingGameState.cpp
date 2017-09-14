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
	std::vector<Minigunner * > * gdiMinigunners = game.getGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		nextMinigunner->Update(frameTime);
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
	std::vector<Minigunner * > * gdiMinigunners = game.getGDIMinigunners();
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

	std::vector<Minigunner * > * gdiMinigunners = game.getGDIMinigunners();

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

std::string PlayingGameState::GetName()
{
	return "Playing";
}