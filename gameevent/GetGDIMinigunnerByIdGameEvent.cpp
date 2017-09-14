#include "GetGDIMinigunnerByIdGameEvent.h"

#include "../game.h"
#include "../gameobject/Minigunner.h"


GetGDIMinigunnerByIdGameEvent::GetGDIMinigunnerByIdGameEvent(Game * aGame, int id) : GameEvent(aGame) {
	foundMinigunner = nullptr;
	this->id = id;
}



Minigunner * GetGDIMinigunnerByIdGameEvent::GetMinigunner() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);
	return foundMinigunner;

}


GameState * GetGDIMinigunnerByIdGameEvent::Process() {
	GameState * newGameState = nullptr;
	std::vector<Minigunner * > * gdiMinigunners = game->getGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->GetId() == id) {
			foundMinigunner = nextMinigunner;
		}
	}

	condition.notify_one();
	return newGameState;
}