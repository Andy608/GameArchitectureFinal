/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "GameObject.h"

GameObject::GameObject(const Sprite& IdleSprite) :
	mpTransform(new Transform()),
	mIdleSprite(IdleSprite),
	mpBounds(new RectBounds(mIdleSprite.getStartingX(), mIdleSprite.getStartingY(), mIdleSprite.getWidth(), mIdleSprite.getHeight()))
{

}

GameObject::~GameObject()
{
	delete mpTransform;
	delete mpBounds;
}

void GameObject::update(float deltaTime)
{
	mpTransform->update(deltaTime);
}
