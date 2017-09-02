#include "GetMinigunnerAtLocationGameEvent.h"

#include "../game.h"
#include "../gameobject/Minigunner.h"

GetMinigunnerAtLocationGameEvent::GetMinigunnerAtLocationGameEvent(Game * aGame, int x, int y) : GameEvent(aGame) {
	this->x = x;
	this->y = y;

}


// TODO: Can probably pull a lot of this common functionality into a base class
Minigunner * GetMinigunnerAtLocationGameEvent::GetMinigunner() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);
	std::vector<Minigunner * > gdiMinigunners = game->getGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners.begin(); iter != gdiMinigunners.end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->PointIsWithin(x, y)) {
			return nextMinigunner;
		}
	}

	return nullptr;

}


GameState * GetMinigunnerAtLocationGameEvent::Process() {
	GameState * newGameState = nullptr;
	condition.notify_one();
	return newGameState;
}