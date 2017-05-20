#pragma once

#include "GameEvent.h"

#include <mutex>

class Minigunner;
class Game;


class GetGDIMinigunnerGameEvent : public GameEvent {

	public:
		GetGDIMinigunnerGameEvent(Game * aGame);
		Minigunner * GetMinigunner();
		virtual void Process();

	private:
		std::condition_variable condition;


};