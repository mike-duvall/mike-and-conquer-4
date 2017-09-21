#include "GetMinigunnerAtLocationGameEvent.h"

#include "../game.h"
#include "../gameobject/Minigunner.h"

GetMinigunnerAtLocationGameEvent::GetMinigunnerAtLocationGameEvent(Game * aGame, int x, int y) : GameEvent(aGame) {
	this->x = x;
	this->y = y;
	foundMinigunner = nullptr;

}


// TODO: Can probably pull a lot of this common functionality into a base class
Minigunner * GetMinigunnerAtLocationGameEvent::GetMinigunner() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);
	return foundMinigunner;
}


GameState * GetMinigunnerAtLocationGameEvent::Process() {
	GameState * newGameState = nullptr;
	std::vector<Minigunner * > * gdiMinigunners = game->GetGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->PointIsWithin(x, y)) {
			foundMinigunner =  nextMinigunner;
		}
	}

	condition.notify_one();
	return newGameState;
}