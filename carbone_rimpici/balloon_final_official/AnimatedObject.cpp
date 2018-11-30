/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

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

void AnimatedObject::update(float deltaTime)
{
	GameObject::update(deltaTime);
}