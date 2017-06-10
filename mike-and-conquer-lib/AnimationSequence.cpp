#include "AnimationSequence.h"



AnimationSequence::AnimationSequence(int frameSwitchThreshold) {
	this->frameSwitchTimer = 0;
	this->frameSwitchThreshold = frameSwitchThreshold;
}


void AnimationSequence::AddFrame(unsigned int frame) {
	frames.push_back(frame);
}

void AnimationSequence::Update() {
	if (!animate) {
		return;
	}

	if (frameSwitchTimer > frameSwitchThreshold) {
		frameSwitchTimer = 0;
		currentAnimationFrameIndex++;
		if (currentAnimationFrameIndex >= frames.size() - 1) {
			currentAnimationFrameIndex = 0;
		}
	}
	else {
		frameSwitchTimer++;
	}

}


unsigned int AnimationSequence::GetCurrentFrame() {
	return frames[currentAnimationFrameIndex];
}


