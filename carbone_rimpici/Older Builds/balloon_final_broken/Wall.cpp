#include "Wall.h"
#include "Game.h"
#include "AssetManager.h"
#include <GraphicsSystem.h>

const std::string Wall::ACCELERATION_ID = "horizontal";

Wall::Wall() :
	GameObject(*Game::getInstance()->getAssetManager()->getSprite("wall_sprite")),
	mIsInUse(false)
{

}

Wall::~Wall()
{
	
}

void Wall::init(bool isCeiling, float x, float y, float horizontalAcceleration, float horizontalVelocity)
{
	mpTransform->reset();
	mpTransform->setPosition(x, y);
	mpTransform->setAcceleration(ACCELERATION_ID, horizontalAcceleration, 0.0f);
	mpTransform->setVelocity(horizontalVelocity, 0.0f);
	mIsOnScreen = !flewOffScreenToLeft();
	mIsInUse = true;
	mIsCeiling = isCeiling;
}

void Wall::update(float deltaTime)
{
	GameObject::update(deltaTime);

	if (mIsCeiling)
	{
		//This is overly complicated :(
		mpBounds->updateBounds(static_cast<int>(std::round(mpTransform->getPosition().getX())),
			-static_cast<int>(std::round(mpTransform->getPosition().getY() - (mIdleSprite.getHeight() * 2.0f) - mpTransform->getOffset().getY() + GraphicsSystem::getDisplayHeight())),
			mIdleSprite.getWidth(), mIdleSprite.getHeight());
	}
	else
	{
		mpBounds->updateBounds(static_cast<int>(std::round(mpTransform->getPosition().getX())),
			static_cast<int>(mpTransform->getOffsetPosition().getY()),
			mIdleSprite.getWidth(), mIdleSprite.getHeight());
	}

	mIsOnScreen = !flewOffScreenToLeft();
}

bool Wall::flewOffScreenToLeft()
{
	//Check if wall is off the screen to the left. 0 x coord is the beginning of the screen.
	return mpBounds->isBoundsLeftOfHorizontalLine(0);
}

void Wall::draw()
{
	GraphicsSystem::draw(mpTransform->getPosition().getX(), mpTransform->getOffsetPosition().getY(), mIdleSprite);
}