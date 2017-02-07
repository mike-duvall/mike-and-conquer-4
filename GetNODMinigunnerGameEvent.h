#pragma once

#include "GameEvent.h"

#include <mutex>

class Minigunner;
class Game;


class GetNODMinigunnerGameEvent : public GameEvent {

public:
	GetNODMinigunnerGameEvent(Game * aGame);
	Minigunner * GetMinigunner();
	virtual void Process();



private:
	std::condition_variable condition;




}; 
