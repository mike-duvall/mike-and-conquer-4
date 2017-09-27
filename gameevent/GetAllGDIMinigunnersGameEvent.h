#pragma once


#include "AsyncGameEvent.h"

#include <vector>

class Minigunner;
class Game;


class GetAllGDIMinigunnersGameEvent : public AsyncGameEvent {

public:
	GetAllGDIMinigunnersGameEvent(Game * aGame);
	std::vector<Minigunner * > * GetAllGdiMinigunners();

protected:
	GameState * ProcessImpl() override;




};