#include "GetMinigunnerAtLocationGameEvent.h"

#include "../game.h"
#include "../gameobject/Minigunner.h"

GetMinigunnerAtLocationGameEvent::GetMinigunnerAtLocationGameEvent(Game * aGame, int x, int y) : NewGameEvent(aGame) {
	this->x = x;
	this->y = y;
}


Minigunner * GetMinigunnerAtLocationGameEvent::GetMinigunner() {
	return static_cast<Minigunner *>(GetResult());

}


GameState * GetMinigunnerAtLocationGameEvent::ProcessImpl() {
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