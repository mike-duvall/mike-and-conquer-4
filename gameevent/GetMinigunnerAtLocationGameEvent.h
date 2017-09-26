#pragma once


#include "NewGameEvent.h"

#include <mutex>

class Minigunner;
class Game;


class GetMinigunnerAtLocationGameEvent : public NewGameEvent {

public:
	GetMinigunnerAtLocationGameEvent(Game * aGame, int x, int y);
	Minigunner * GetMinigunner();


protected:
	GameState * ProcessImpl() override;


private:
	int x;
	int y;

};