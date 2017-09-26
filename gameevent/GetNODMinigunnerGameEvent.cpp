#include "GetNODMinigunnerGameEvent.h"

#include "../game.h"

GetNODMinigunnerGameEvent::GetNODMinigunnerGameEvent(Game * aGame) : NewGameEvent(aGame) {

}


Minigunner * GetNODMinigunnerGameEvent::GetMinigunner() {
	return (Minigunner *)GetResult();
}


GameState * GetNODMinigunnerGameEvent::ProcessImpl() {
	GameState * newGameState = nullptr;
	result = game->GetNODMinigunner();
	return nullptr;
}