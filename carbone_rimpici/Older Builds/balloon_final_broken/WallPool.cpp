#include "WallPool.h"
#include "RectBounds.h"

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

Wall* WallPool::createWall(bool isCeiling, float x, float y, float horizontalAcceleration, float horizontalVelocity)
{
	Wall* newWall = mpFirstAvailableWall;
	mpFirstAvailableWall = newWall->getNext();

	if (newWall)
	{
		newWall->init(isCeiling, x, y, horizontalAcceleration, horizontalVelocity);
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

		if (!mpWalls[i].isOnScreen() && mpWalls[i].mIsInUse)
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
		if (mpWalls[i].isInUse())
		{
			mpWalls[i].draw();
		}
	}
}

bool WallPool::checkCollision(GameObject* pObject)
{
	bool isColliding = false;
	for (int i = 0; i < mPOOL_SIZE; ++i)
	{
		if (mpWalls[i].mpBounds->isIntersecting(pObject->getRectBounds()))
		{
			isColliding = true;
			break;
		}
	}

	return isColliding;
}