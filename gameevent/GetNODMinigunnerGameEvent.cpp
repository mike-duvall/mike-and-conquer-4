#include "GetNODMinigunnerGameEvent.h"

#include "../game.h"

GetNODMinigunnerGameEvent::GetNODMinigunnerGameEvent(Game * aGame) : AsyncGameEvent(aGame) {

}


Minigunner * GetNODMinigunnerGameEvent::GetMinigunner() {
	return static_cast<Minigunner *>(GetResult());
}


GameState * GetNODMinigunnerGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	result = game->GetNODMinigunner();
	return nullptr;
}