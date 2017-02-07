#include "GetNODMinigunnerGameEvent.h"


#include "game.h"


GetNODMinigunnerGameEvent::GetNODMinigunnerGameEvent(Game * aGame) : GameEvent(aGame) {

}


//Can do same kind of wait on condition in the createGDI rest call as well
//general pattern, post event, wait for it to be completed, then return

Minigunner * GetNODMinigunnerGameEvent::GetMinigunner() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);
	return game->GetNODMinigunner();
}


void GetNODMinigunnerGameEvent::Process() {
	condition.notify_one();
}