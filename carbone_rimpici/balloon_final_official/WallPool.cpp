/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "WallPool.h"
#include "RectBounds.h"
#include "SaveFile.h"
#include "SaveManager.h"

WallPool::WallPool(int poolSize) : 
	mPOOL_SIZE(poolSize),
	mpWalls(new Wall[mPOOL_SIZE])
{
	mpFirstAvailableWall = &mpWalls[0];

	int i;
	for (i = 0; i < mPOOL_SIZE - 1; ++i)
	{
		mpWalls[i].setNext(&mpWalls[i + 1]);
	}

	mpWalls[mPOOL_SIZE - 1].setNext(nullptr);
}

WallPool::~WallPool()
{
	delete[] mpWalls;
}

Wall* WallPool::createWall(float x, float y, float horizontalAcceleration, float horizontalVelocity)
{
	Wall* newWall = mpFirstAvailableWall;
	mpFirstAvailableWall = newWall->getNext();

	if (newWall)
	{
		newWall->init(x, y, horizontalAcceleration, horizontalVelocity);
	}
	else
	{
		std::cout << "ERROR CREATING NEW WALL FROM OBJECT POOL." << std::endl;
	}

	return newWall;
}

void WallPool::update(float deltaTime)
{
	int i;
	for (i = 0; i < mPOOL_SIZE; ++i)
	{
		mpWalls[i].update(deltaTime);

		if (!mpWalls[i].mIsOnScreen && mpWalls[i].mIsInUse)
		{
			mpWalls[i].mIsInUse = false;
			mpWalls[i].setNext(mpFirstAvailableWall); 
			mpFirstAvailableWall = &mpWalls[i];
		}
	}
}

void WallPool::draw()
{
	int i;
	for (i = 0; i < mPOOL_SIZE; ++i)
	{
		if (mpWalls[i].mIsInUse)
		{
			mpWalls[i].draw();
		}
	}
}

bool WallPool::checkCollision(RectBounds* bounds)
{
	bool isColliding = false;
	for (int i = 0; i < mPOOL_SIZE; ++i)
	{
		if (mpWalls[i].mIsInUse && mpWalls[i].mpBounds->isIntersecting(bounds))
		{
			isColliding = true;
			break;
		}
	}

	return isColliding;
}