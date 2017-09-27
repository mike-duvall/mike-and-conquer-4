#include "AsyncGameEvent.h"



AsyncGameEvent::AsyncGameEvent(Game * aGame) {
	this->game = aGame;
	this->result = nullptr;
}



GameState * AsyncGameEvent::Process() {
	GameState * newGameState = ProcessImpl();
	condition.notify_one();
	return newGameState;
}



void * AsyncGameEvent::GetResult() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);
	return result;
}

