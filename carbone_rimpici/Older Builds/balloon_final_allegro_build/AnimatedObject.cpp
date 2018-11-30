#include "AnimatedObject.h"

AnimatedObject::AnimatedObject(const Sprite& pIdleSprite) :
	GameObject(pIdleSprite)
{

}

AnimatedObject::~AnimatedObject()
{
	auto iter = mAnimationList.begin();
	for (; iter != mAnimationList.end(); ++iter)
	{
		delete iter->second;
	}

	mAnimationList.clear();
}

void AnimatedObject::addAnimation(std::string state, Animation* pAnimation)
{
	if (!mAnimationList.insert(std::make_pair(state, pAnimation)).second)
	{
		std::cout << "Animation is already implemented in the animation state list!" << std::endl;
		delete pAnimation;
	}
}
