#include "NewGameEvent.h"



NewGameEvent::NewGameEvent(Game * aGame) {
	this->game = aGame;
	this->result = nullptr;
}



GameState * NewGameEvent::Process() {
	GameState * newGameState = ProcessImpl();
	condition.notify_one();
	return newGameState;
}



void * NewGameEvent::GetResult() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);
	return result;
}

