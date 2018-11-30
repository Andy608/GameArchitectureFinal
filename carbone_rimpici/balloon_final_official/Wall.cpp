/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "Wall.h"
#include <GraphicsSystem.h>

const std::string Wall::ACCELERATION_ID = "horizontal";

Wall::Wall(const Sprite& sprite) :
	GameObject(sprite),
	mIsInUse(false)
{

}

Wall::~Wall()
{
	
}

void Wall::init(float x, float y, float horizontalAcceleration, float horizontalVelocity)
{
	mpTransform->reset();
	mpTransform->setPosition(x, y);
	mpTransform->setAcceleration(ACCELERATION_ID, horizontalAcceleration, 0.0f);
	mpTransform->setVelocity(horizontalVelocity, 0.0f);
	mIsOnScreen = !flewOffScreenToLeft();
	mIsInUse = true;
}

void Wall::update(float deltaTime)
{
	GameObject::update(deltaTime);

	mpBounds->updateBounds(static_cast<int>(std::round(mpTransform->getPosition().getX())),
		static_cast<int>(std::round(mpTransform->getPosition().getY())),
		mIdleSprite.getWidth(), mIdleSprite.getHeight());

	mIsOnScreen = !flewOffScreenToLeft();
}

bool Wall::flewOffScreenToLeft()
{
	//Check if wall is off the screen to the left. 0 x coord is the beginning of the screen.
	return mpBounds->isBoundsLeftOfHorizontalLine(0);
}

void Wall::draw()
{
	//Debug draws hitbox when uncommented.
	//GraphicsSystem::drawRect(mpBounds->mStartingX, mpBounds->mStartingY, mpBounds->mWidth, mpBounds->mHeight, Color(1.0, 0.0, 0.0, 1.0));
	GraphicsSystem::draw(mpTransform->getPosition().getX(), mpTransform->getPosition().getY(), mIdleSprite);
}