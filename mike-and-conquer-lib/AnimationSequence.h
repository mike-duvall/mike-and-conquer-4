#pragma once


#include <vector>


class AnimationSequence {



public:
	AnimationSequence(int frameSwitchThreshold);
	void AddFrame(unsigned int);
	void Update();
	void SetAnimate(bool newValue) { animate = newValue; }

	// ? void Update(float frameTime);
	unsigned int GetCurrentFrame();
	void SetCurrentFrameIndex(unsigned int currentAnimationFrame) { this->currentAnimationFrameIndex = currentAnimationFrame;  }

private:

	std::vector<unsigned int> frames;
	int frameSwitchTimer;
	int frameSwitchThreshold;
	unsigned int currentAnimationFrameIndex;
	bool animate;

};