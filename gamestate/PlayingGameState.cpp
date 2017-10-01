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



void PlayingGameState::UpdateMinigunners(float frameTime, std::vector<Minigunner * > * minigunners) {
	std::vector<Minigunner *>::iterator iter;
	for (iter = minigunners->begin(); iter != minigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		nextMinigunner->Update(frameTime);
	}
}



void PlayingGameState::UpdateGdiMinigunners(float frameTime) {
	UpdateMinigunners(frameTime, game.GetGDIMinigunners());
}


void PlayingGameState::UpdateNodMinigunners(float frameTime) {
	UpdateMinigunners(frameTime, game.GetNodMinigunners());
}


GameState * PlayingGameState::Update(float frameTime) {

	game.ProcessGameEvents();


	Input * input = game.GetInput();
	if (input->isLeftMouseDown()) {
		HandleLeftMouseDown(input);
	}

	UpdateGdiMinigunners(frameTime);
	UpdateNodMinigunners(frameTime);


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



//	if (enemyMinigunner1 != nullptr && enemyMinigunner1->GetHealth() <= 0) {
//		return new MissionAccomplishedGameState(game);
//	}
	if(NodMinigunnersExistAndAreAllDead()) {
		return new MissionAccomplishedGameState(game);
	}

	if(GdiMinigunnersExistAndAreAllDead()) {
		return new MissionFailedGameState(game);
	}

	return this;

}



// TODO: Refactor to remove duplication
bool PlayingGameState::NodMinigunnersExistAndAreAllDead() {
	std::vector<Minigunner * > * minigunners = game.GetNodMinigunners();
	if (minigunners->size() == 0) {
		return false;
	}

	std::vector<Minigunner *>::iterator iter;
	for (iter = minigunners->begin(); iter != minigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->GetHealth() > 0) {
			return false;
		}
	}

	return true;
}



bool PlayingGameState::GdiMinigunnersExistAndAreAllDead()
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



// TODO Refactor this common code across GameStats
void PlayingGameState::DrawMinigunners( std::vector<Minigunner * > * minigunners) {
	std::vector<Minigunner *>::iterator iter;
	for (iter = minigunners->begin(); iter != minigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;

		//nextMinigunner->Draw();
		if (nextMinigunner->GetHealth() > 0) {
			// TODO  Check here whether health is greater than zero for GDI?
			nextMinigunner->Draw();
		}

	}
}



void PlayingGameState::DrawGdiMinigunners() {
	DrawMinigunners(game.GetGDIMinigunners());
}


void PlayingGameState::DrawNodMinigunners() {
	DrawMinigunners(game.GetNodMinigunners());
}



void PlayingGameState::Render() {

	std::vector<Minigunner * > * gdiMinigunners = game.GetGDIMinigunners();

//	std::vector<Minigunner *>::iterator iter;
//	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
//		Minigunner * nextMinigunner = *iter;
//		nextMinigunner->Draw();
//	}
//
//	Minigunner * enemyMinigunner1 = game.GetNODMinigunner();
//	if (enemyMinigunner1 != NULL) {
//		if (enemyMinigunner1->GetHealth() > 0) {
//			enemyMinigunner1->Draw();
//		}
//	}

	DrawGdiMinigunners();
	DrawNodMinigunners();

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


	std::vector<Minigunner * > * nodMinigunners = game.GetNodMinigunners();
	std::vector<Minigunner *>::iterator nodIter;
	for (nodIter = nodMinigunners->begin(); nodIter != nodMinigunners->end(); ++nodIter) {
		Minigunner * nextNodMinigunner = *nodIter;
		if(nextNodMinigunner->PointIsWithin(mouseX, mouseY)) {

			std::vector<Minigunner * > * gdiMinigunners = game.GetGDIMinigunners();
			std::vector<Minigunner *>::iterator gidIter;
			for (gidIter = gdiMinigunners->begin(); gidIter != gdiMinigunners->end(); ++gidIter) {
				Minigunner * nextMinigunner = *gidIter;
				if (nextMinigunner->GetIsSelected()) {
					nextMinigunner->OrderToMoveToAttackEnemyUnit(nextNodMinigunner);
				}
			}

			return true;
		}

	}

//	Minigunner * enemyMinigunner = game.GetNODMinigunner();
//	if (enemyMinigunner != nullptr && enemyMinigunner->PointIsWithin(mouseX, mouseY)) {
//		std::vector<Minigunner * > * gdiMinigunners = game.GetGDIMinigunners();
//
//		std::vector<Minigunner *>::iterator iter;
//		for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
//			Minigunner * nextMinigunner = *iter;
//			if (nextMinigunner->GetIsSelected()) {
//				nextMinigunner->OrderToMoveToAttackEnemyUnit(enemyMinigunner);
//			}
//		}
//
//		return true;
//
//	}

	return false;
}

std::string PlayingGameState::GetName() {
	return "Playing";
}