/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "Animation.h"

Animation::Animation(float frameLength, bool loopAnimation) :
	Animation(std::vector<Sprite*>(), frameLength, loopAnimation)
{

}

Animation::Animation(std::vector<Sprite*> animationFrames, float frameLength, bool loopAnimation) :
	mFrames(animationFrames),
	mFrameLength(frameLength),
	mLoopAnimation(loopAnimation),
	mCurrentSpriteIndex(0),
	mElapsedTime(0)
{

}

Animation::~Animation()
{
	
}

void Animation::update(float deltaTime)
{
	mElapsedTime += deltaTime;

	if (mElapsedTime >= mFrameLength)
	{
		mElapsedTime = 0;

		if (mLoopAnimation || mCurrentSpriteIndex < mFrames.size() - 1)
		{
			mCurrentSpriteIndex = (mCurrentSpriteIndex + 1) % mFrames.size();
		}
	}
}

void Animation::setFrameLength(float frameLength)
{
	mFrameLength = frameLength;
}

void Animation::setFrameLengthOffset(float frameLengthOffset)
{
	mElapsedTime = frameLengthOffset;
}

void Animation::setFrameIndex(unsigned int animationFrameIndex)
{
	mCurrentSpriteIndex = animationFrameIndex % mFrames.size();
}

const Sprite& Animation::getCurrentSprite() const
{
	return *mFrames.at(mCurrentSpriteIndex);
}

const float& Animation::getFrameLength() const
{
	return mFrameLength;
}

void Animation::addFrame(Sprite* frame)
{
	mFrames.push_back(frame);
}

void Animation::addFrames(const std::vector<Sprite*>& frames)
{
	unsigned int i;
	for (i = 0; i < frames.size(); ++i)
	{
		mFrames.push_back(frames.at(i));
	}
}