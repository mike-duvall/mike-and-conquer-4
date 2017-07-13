#include "MissionFailedMessage.h"



#include "GameSprite.h"
#include "Game.h"
#include "AnimationSequence.h"

MissionFailedMessage::MissionFailedMessage(Game & game) {

	missionGameSprite = new GameSprite(game.GetGraphics()->Get3Ddevice(), "assets/Mission.png", graphicsNS::MAGENTA);
	AnimationSequence * missionAnimationSequence = new AnimationSequence(10);
	missionAnimationSequence->AddFrame(0);
	missionGameSprite->AddAnimationSequence(0, missionAnimationSequence);
	missionGameSprite->SetCurrentAnimationSequenceIndex(0);
	missionGameSprite->setScaling(1.0);

	failedGameSprite = new GameSprite(game.GetGraphics()->Get3Ddevice(), "assets/Failed.png", graphicsNS::MAGENTA);
	AnimationSequence * accomplishedAnimationSequence = new AnimationSequence(10);
	accomplishedAnimationSequence->AddFrame(0);
	failedGameSprite->AddAnimationSequence(0, accomplishedAnimationSequence);
	failedGameSprite->SetCurrentAnimationSequenceIndex(0);
	failedGameSprite->setScaling(1.0);

}


void MissionFailedMessage::Draw() {
	missionGameSprite->Draw(0, 800, 400);
	failedGameSprite->Draw(0, 800, 450);

}
