#pragma once


#include "AsyncGameEvent.h"

#include <vector>

class Minigunner;
class Game;


class GetAllNodMinigunnersGameEvent : public AsyncGameEvent {

public:
	GetAllNodMinigunnersGameEvent(Game * aGame);
	std::vector<Minigunner * > * GetAllNodMinigunners();

protected:
	GameState * ProcessImpl() override;




};
