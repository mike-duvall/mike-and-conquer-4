#include "GetGDIMinigunnerGameEvent.h"


#include "game.h"


GetGDIMinigunnerGameEvent::GetGDIMinigunnerGameEvent(Game * aGame) : GameEvent(aGame) {

}


//Can do same kind of wait on condition in the createGDI rest call as well
//general pattern, post event, wait for it to be completed, then return

Minigunner * GetGDIMinigunnerGameEvent::GetMinigunner() {
	std::mutex dummyMutex;
	std::unique_lock<std::mutex> locker(dummyMutex);
	condition.wait(locker);
	return game->GetGDIMinigunner();
}


void GetGDIMinigunnerGameEvent::Process() {
	condition.notify_one();
}