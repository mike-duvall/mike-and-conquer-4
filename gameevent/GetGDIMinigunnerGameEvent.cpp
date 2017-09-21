#include "GetGDIMinigunnerGameEvent.h"

#include "../game.h"


GetGDIMinigunnerGameEvent::GetGDIMinigunnerGameEvent(Game * aGame) : GameEvent(aGame) {
	foundMinigunner = nullptr;

}



//Can do same kind of wait on condition in the createGDI rest call as well
//general pattern, post event, wait for it to be completed, then return

Minigunner * GetGDIMinigunnerGameEvent::GetMinigunner() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);
	return foundMinigunner;

}


GameState * GetGDIMinigunnerGameEvent::Process() {
	GameState * newGameState = nullptr;
	std::vector<Minigunner * > * gdiMinigunners = game->GetGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		foundMinigunner = nextMinigunner;
	}

	condition.notify_one();
	return newGameState;
}