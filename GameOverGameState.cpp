#include "GameOverGameState.h"



GameOverGameState::GameOverGameState(Game & game) : GameState(game) {

}

GameState * GameOverGameState::Update(float frameTime) {
	return this;

}


void GameOverGameState::Render() {
	//Consider how to  handle if we want GameOver to draw different background color
	//	Does rendering and everything go in Render?
	//	Do we just have one Update method, that includes render
	//	And maybe GameState has base functions that can be called to begin and end scene


}
