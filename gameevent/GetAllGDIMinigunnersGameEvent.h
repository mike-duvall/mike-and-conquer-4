#pragma once


#include "GameEvent.h"

#include <mutex>
#include <vector>

class Minigunner;
class Game;


class GetAllGDIMinigunnersGameEvent : public GameEvent {

public:
	GetAllGDIMinigunnersGameEvent(Game * aGame);
	std::vector<Minigunner * > * GetAllGDIMinigunners();

	virtual GameState * Process();

private:
	std::condition_variable condition;
	std::vector<Minigunner * > * foundMinigunners;


};