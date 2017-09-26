#pragma once


#include "NewGameEvent.h"

#include <vector>

class Minigunner;
class Game;


class GetAllGDIMinigunnersGameEvent : public NewGameEvent {

public:
	GetAllGDIMinigunnersGameEvent(Game * aGame);
	std::vector<Minigunner * > * GetAllGdiMinigunners();

protected:
	GameState * ProcessImpl() override;




};