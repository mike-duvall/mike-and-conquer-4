#pragma once

class GameSprite;
class Game;

class MissionAccomplishedMessage {
public:

	MissionAccomplishedMessage(Game & game);
	void Draw();

private:

	GameSprite * missionGameSprite;
	GameSprite * accomplishedGameSprite;
};
