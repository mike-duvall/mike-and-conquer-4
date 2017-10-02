#include "GetNodMinigunnerByIdGameEvent.h"

#include "../game.h"
#include "../gameobject/Minigunner.h"


GetNodMinigunnerByIdGameEvent::GetNodMinigunnerByIdGameEvent(Game * aGame, int id) : AsyncGameEvent(aGame) {
	this->id = id;
}



Minigunner * GetNodMinigunnerByIdGameEvent::GetMinigunner() {
	return static_cast<Minigunner *>(GetResult());
}


GameState * GetNodMinigunnerByIdGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	std::vector<Minigunner * > * gdiMinigunners = game->GetNodMinigunners();

	std::vector<Minigunner *>::iterator iter;
	for (iter = gdiMinigunners->begin(); iter != gdiMinigunners->end(); ++iter) {
		Minigunner * nextMinigunner = *iter;
		if (nextMinigunner->GetId() == id) {
			result = nextMinigunner;
		}
	}

	return newGameState;
}