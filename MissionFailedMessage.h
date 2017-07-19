#pragma once



class GameSprite;
class Game;

class MissionFailedMessage {
public:

	MissionFailedMessage(Game & game);
	void Draw();

private:

	GameSprite * missionGameSprite;
	GameSprite * failedGameSprite;
};

