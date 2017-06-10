#include "GameOverMessage.h"



#include "GameSprite.h"
#include "Game.h"
#include "AnimationSequence.h"

GameOverMessage::GameOverMessage(Game & game) {

	
	missionGameSprite = new GameSprite(game.GetGraphics()->Get3Ddevice(), "assets/Mission.png", graphicsNS::MAGENTA);
	AnimationSequence * missionAnimationSequence = new AnimationSequence(10);
	missionAnimationSequence->AddFrame(0);
	missionGameSprite->AddAnimationSequence(0, missionAnimationSequence);
	missionGameSprite->SetCurrentAnimationSequenceIndex(0);
	missionGameSprite->setScaling(1.0);

	accomplishedGameSprite = new GameSprite(game.GetGraphics()->Get3Ddevice(), "assets/Accomplished.png", graphicsNS::MAGENTA);
	AnimationSequence * accomplishedAnimationSequence = new AnimationSequence(10);
	accomplishedAnimationSequence->AddFrame(0);
	accomplishedGameSprite->AddAnimationSequence(0, accomplishedAnimationSequence);
	accomplishedGameSprite->SetCurrentAnimationSequenceIndex(0);
	accomplishedGameSprite->setScaling(1.0);


}


void GameOverMessage::Draw() {
	missionGameSprite->Draw(0, 800, 400);
	accomplishedGameSprite->Draw(0, 800, 450);

}
