#include "GetGdiMinigunnerAtLocationGameEvent.h"

#include "../game.h"
#include "../gameobject/Minigunner.h"

GetGdiMinigunnerAtLocationGameEvent::GetGdiMinigunnerAtLocationGameEvent(Game * aGame, int x, int y) : AsyncGameEvent(aGame) {
	this->x = x;
	this->y = y;
}


Minigunner * GetGdiMinigunnerAtLocationGameEvent::GetMinigunner() {
	return static_cast<Minigunner *>(GetResult());

}


GameState * GetGdiMinigunnerAtLocationGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	std::vector<Minigunner * > * gdiMinigunners = game->GetGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->PointIsWithin(x, y)) {
			result =  nextMinigunner;
		}
	}

	return newGameState;
}