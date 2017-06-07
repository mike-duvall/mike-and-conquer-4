#include "GameOverGameState.h"

#include "graphics.h"
#include "Game.h"

GameOverGameState::GameOverGameState(Game & game) : GameState(game) {

}

GameState * GameOverGameState::Update(float frameTime) {

	game.ProcessGameEvents();
	Graphics * graphics = game.GetGraphics();
	graphics->BeginScene(graphicsNS::CYAN);
	this->Render();
	graphics->endScene();
	graphics->ShowBackbuffer();

	return this;

}


void GameOverGameState::Render() {
	//Consider how to  handle if we want GameOver to draw different background color
	//	Does rendering and everything go in Render?
	//	Do we just have one Update method, that includes render
	//	And maybe GameState has base functions that can be called to begin and end scene


}
