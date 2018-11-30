/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <Trackable.h>
#include <vector>
#include "Sprite.h"

class Animation : public Trackable
{
public:
	Animation(float frameLength, bool loopAnimation);
	Animation(std::vector<Sprite*> animationFrames, float frameLength, bool loopAnimation);
	~Animation();

	void update(float deltaTime);

	void setFrameLength(float frameLength);
	void setFrameLengthOffset(float frameLengthOffset);
	void setFrameIndex(unsigned int animationFrameIndex);
	const Sprite& getCurrentSprite() const;
	const float& getFrameLength() const;

	void addFrame(Sprite* frame);
	void addFrames(const std::vector<Sprite*>& frames);

	inline const float getElapsedTime() const { return mElapsedTime; };
	inline const unsigned int getCurrentSpriteIndex() const { return mCurrentSpriteIndex; };

private:
	std::vector<Sprite*> mFrames;
	float mFrameLength;
	bool mLoopAnimation;
	unsigned int mCurrentSpriteIndex;
	float mElapsedTime;
};

#endif