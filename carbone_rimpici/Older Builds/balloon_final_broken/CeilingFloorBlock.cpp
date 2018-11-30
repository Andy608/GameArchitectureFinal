#include "CeilingFloorBlock.h"
#include <GraphicsSystem.h>

CeilingFloorBlock::CeilingFloorBlock(const Sprite& idleSprite, Vector2D startingLocation, Vector2D startingVelocity) :
	AnimatedObject(idleSprite),
	mIsOnScreen(false)
{
	mpTransform->setPosition(startingLocation);
	mpTransform->setVelocity(startingVelocity);
}

CeilingFloorBlock::~CeilingFloorBlock()
{

}

void CeilingFloorBlock::update(float deltaTime)
{
	AnimatedObject::update(deltaTime);
}

void CeilingFloorBlock::draw()
{
	GraphicsSystem::draw(mpTransform->getPosition().getX(), mpTransform->getPosition().getY(), mIdleSprite);
}