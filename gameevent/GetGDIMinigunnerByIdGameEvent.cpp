#include "GetGDIMinigunnerByIdGameEvent.h"

#include "../game.h"
#include "../gameobject/Minigunner.h"


GetGDIMinigunnerByIdGameEvent::GetGDIMinigunnerByIdGameEvent(Game * aGame, int id) : AsyncGameEvent(aGame) {
	this->id = id;
}



Minigunner * GetGDIMinigunnerByIdGameEvent::GetMinigunner() {
	return static_cast<Minigunner *>(GetResult());
}


GameState * GetGDIMinigunnerByIdGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	std::vector<Minigunner * > * gdiMinigunners = game->GetGDIMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->GetId() == id) {
			result = nextMinigunner;
		}
	}

	return newGameState;
}