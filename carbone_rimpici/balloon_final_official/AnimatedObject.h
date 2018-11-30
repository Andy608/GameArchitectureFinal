/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef ANIMATED_OBJECT_H_
#define ANIMATED_OBJECT_H_

#include <map>
#include <string>
#include "GameObject.h"
#include "Animation.h"

class AnimatedObject : public GameObject
{
public:
	AnimatedObject(const Sprite& pIdleSprite);
	virtual ~AnimatedObject();

	void addAnimation(std::string state, Animation* pAnimation);

	virtual void update(float delta) = 0;
	virtual void draw() = 0;

private:
	//List of animations depending on state.
	std::map<std::string, Animation*> mAnimationList;
};

#endif