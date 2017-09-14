#pragma once


#include "GameEvent.h"

#include <mutex>

class Minigunner;
class Game;


class GetGDIMinigunnerByIdGameEvent : public GameEvent {

public:
	GetGDIMinigunnerByIdGameEvent(Game * aGame, int id);
	Minigunner * GetMinigunner();
	virtual GameState * Process();

private:
	std::condition_variable condition;
	Minigunner * foundMinigunner;
	int id;


};