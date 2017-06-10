#pragma once



class GameSprite;
class Game;

class GameOverMessage {
public:

	GameOverMessage(Game & game);
	void Draw();

private:

	GameSprite * missionGameSprite;
	GameSprite * accomplishedGameSprite;
};
