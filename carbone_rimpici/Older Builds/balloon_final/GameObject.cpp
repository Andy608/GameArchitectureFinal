/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "GameObject.h"

GameObject::GameObject(const Sprite& IdleSprite) :
	mpTransform(new Transform()),
	mpIdleSprite(IdleSprite)
{

}

GameObject::~GameObject()
{
	delete mpTransform;
}

void GameObject::update(float deltaTime)
{
	mpTransform->update(deltaTime);
}
