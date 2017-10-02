#include "GetNodMinigunnerAtLocationGameEvent.h"

#include "../game.h"
#include "../gameobject/Minigunner.h"

GetNodMinigunnerAtLocationGameEvent::GetNodMinigunnerAtLocationGameEvent(Game * aGame, int x, int y) : AsyncGameEvent(aGame) {
	this->x = x;
	this->y = y;
}


Minigunner * GetNodMinigunnerAtLocationGameEvent::GetMinigunner() {
	return static_cast<Minigunner *>(GetResult());

}


GameState * GetNodMinigunnerAtLocationGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	std::vector<Minigunner * > * gdiMinigunners = game->GetNodMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->PointIsWithin(x, y)) {
			result = nextMinigunner;
		}
	}

	return newGameState;
}