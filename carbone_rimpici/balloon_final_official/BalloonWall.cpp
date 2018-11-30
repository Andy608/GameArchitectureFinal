/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "BalloonWall.h"
#include "HeightGenerator.h"
#include <GraphicsSystem.h>

const float BalloonWall::TURN_AROUND_COOLDOWN = 1000;//1 second cooldown

int BalloonWall::getRandomBalloonIndex(unsigned int rows, unsigned int columns)
{
	int randomIndexX = HeightGenerator::getRandomInt(0, rows - 1);
	int randomIndexY = HeightGenerator::getRandomInt(0, columns - 1);
	return ((randomIndexY * rows) + randomIndexX);
}

BalloonWall::BalloonWall(const SpriteSheet& spriteSheet, int spriteSheetIndex, int minHeight, int maxHeight, int startingSpeed) :
	Wall(*spriteSheet.getSprites().at(spriteSheetIndex)),
	mSpriteSheetIndex(spriteSheetIndex),
	mMinHeight(minHeight),
	mMaxHeight(maxHeight),
	mSpeed((float)startingSpeed)
{
	
}

BalloonWall::~BalloonWall()
{

}

void BalloonWall::update(float deltaTime)
{
	Wall::update(deltaTime);
	mpTransform->setVelocity(mpTransform->getVelocity().getX(), mSpeed);

	if (mTurnAroundCoolDown > 0)
	{
		mTurnAroundCoolDown -= deltaTime;
	}
}

void BalloonWall::draw()
{
	GraphicsSystem::draw(mpTransform->getPosition().getX(), mpTransform->getPosition().getY(), mIdleSprite);
}