#include "WallManager.h"
#include "Game.h"
#include "AssetManager.h"
#include <GraphicsSystem.h>

const std::string WallManager::ACCELERATION_ID = "horizontal";

WallManager::WallManager() :
	//Multiply by 3 because there are top walls, bottom walls, and middle walls
	mSpriteDimensions(Vector2D(Game::getInstance()->getAssetManager()->getSprite("wall_sprite")->getWidth(), Game::getInstance()->getAssetManager()->getSprite("wall_sprite")->getHeight())),
	mpWallPool(new WallPool(getAmountOfWallsFitOnScreen() * 3)),
	mIsMoving(false),
	mpWallTransform(new Transform()),
	mpHeightGenerator(new HeightGenerator())
{
	mpWallTransform->setAcceleration(ACCELERATION_ID, static_cast<float>(*Game::getInstance()->getAssetManager()->getValue("starting_acceleration_x")), 0.0f);
	mpWallTransform->setVelocity(static_cast<float>(*Game::getInstance()->getAssetManager()->getValue("starting_velocity_x")), 0.0f);

	mpHeightGenerator->setMinHeightOffset(-mSpriteDimensions.getY());
	mpHeightGenerator->setMaxHeightOffset(mSpriteDimensions.getY());
	mpHeightGenerator->setFrequency(40.0f);
	mpHeightGenerator->setMagnitude(1.0f);
	
	mCeilingYBaseline = -(mSpriteDimensions.getY() / 1.5f);
	mFloorYBaseline = -(mSpriteDimensions.getY() / 2.5f);

	initWalls();
}

WallManager::~WallManager()
{
	delete mpWallPool;
	delete mpWallTransform;
	delete mpHeightGenerator;
}

void WallManager::initWalls()
{
	int amountOfSpritesOnScreen = getAmountOfWallsFitOnScreen();
	
	mCeilingList.clear();

	int i;
	for (i = 0; i < amountOfSpritesOnScreen; ++i)
	{
		Wall* newWall = createWall(true, static_cast<float>(i * mSpriteDimensions.getX()), mCeilingYBaseline,
			mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());

		newWall->mpTransform->setOffset(0, -mpHeightGenerator->getNextHeight());

		if (newWall)
		{
			mCeilingList.push_back(newWall);
		}
	}

	for (i = 0; i < amountOfSpritesOnScreen; ++i)
	{
		Wall* newWall = createWall(false, static_cast<float>(i * mSpriteDimensions.getX()), mFloorYBaseline,
			mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());

		newWall->mpTransform->setOffset(0, mCeilingList.at(i)->mpTransform->getOffset().getY() + GraphicsSystem::getDisplayHeight());

		if (newWall)
		{
			mFloorList.push_back(newWall);
		}
	}
}

void WallManager::update(float deltaTime)
{
	mpWallTransform->update(deltaTime);
	mpWallPool->update(deltaTime);

	for (unsigned int i = 0; i < mCeilingList.size(); ++i)
	{
		if (!mCeilingList.at(i)->isInUse())
		{
			float nextHeight = mpHeightGenerator->getNextHeight();

			Wall* newCeilingWall = createWall(true, mCeilingList.at(mCeilingList.size() - 1)->getTransform().getPosition().getX() + mSpriteDimensions.getX(), mCeilingYBaseline,
				mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());

			newCeilingWall->mpTransform->setOffset(0, -nextHeight);

			Wall* newFloorWall = createWall(false, mFloorList.at(mFloorList.size() - 1)->getTransform().getPosition().getX() + mSpriteDimensions.getX(), mFloorYBaseline + GraphicsSystem::getDisplayHeight(),
				mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());

			newFloorWall->mpTransform->setOffset(0, -nextHeight);
			//newFloorWall->mpTransform->setOffset(0, mCeilingList.at(i)->mpTransform->getOffset().getY() + GraphicsSystem::getDisplayHeight());

			mCeilingList.erase(mCeilingList.begin() + i);
			mFloorList.erase(mFloorList.begin() + i);

			if (newCeilingWall)
			{
				mCeilingList.push_back(newCeilingWall);
			}

			if (newFloorWall)
			{
				mFloorList.push_back(newFloorWall);
			}

			break;
		}
	}
}

void WallManager::draw()
{
	mpWallPool->draw();
}

int WallManager::getAmountOfWallsFitOnScreen()
{
	return static_cast<int>((GraphicsSystem::getInstance()->getDisplayWidth() / mSpriteDimensions.getX())) + 2;
}

Wall* WallManager::createWall(bool isCeiling, float x, float y, float acceleration, float velocity)
{
	return mpWallPool->createWall(isCeiling, x, y, acceleration, velocity);
}

bool WallManager::isWallCollidingWith(GameObject* pObject)
{
	return mpWallPool->checkCollision(pObject);
}