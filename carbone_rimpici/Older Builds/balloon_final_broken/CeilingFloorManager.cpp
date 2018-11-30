#include "CeilingFloorManager.h"
#include <GraphicsSystem.h>
#include <random>
#include "SaveManager.h"
#include "Sprite.h"
#include <iostream>
#include "Game.h"

CeilingFloorManager::CeilingFloorManager(const Sprite& ceilingFloorSprite, const Sprite& wallSprite, double blockVelocity, double velocityIncrement) :
	mCeilingFloorSprite(ceilingFloorSprite),
	mFloatingWallSprite(wallSprite),
	mVelocity(Vector2D((float)(blockVelocity), 0.0)),
	mVelocityIncrement(velocityIncrement)
{
	mCeilingBlocks.push_back(new CeilingFloorBlock(ceilingFloorSprite, Vector2D(GraphicsSystem::getDisplayWidth(), 0), mVelocity));
	mFloorBlocks.push_back(new CeilingFloorBlock(ceilingFloorSprite, Vector2D(GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight() - mCeilingFloorSprite.getHeight()), mVelocity));
}

CeilingFloorManager::~CeilingFloorManager()
{
	cleanup();
}

void CeilingFloorManager::update(float deltaTime)
{
	int ceilingCount = mCeilingBlocks.size();
	int floorCount = mFloorBlocks.size();

	//loops through and updates all ceiling blocks
	for (int i = 0; i < ceilingCount; i++)
	{
		mCeilingBlocks[i]->update(deltaTime);

		//checks first and last blocks
		if (i == 0 || i == mCeilingBlocks.size() - 1)
		{
			const Transform& objTransform = mCeilingBlocks[i]->getTransform();
			const Sprite& objSprite = mFloorBlocks[i]->getIdleSprite();

			//makes new block on right if current one is one screen
			if (!mCeilingBlocks[i]->isOnScreen() && (objTransform.getPosition().getX() + objSprite.getWidth()) < GraphicsSystem::getDisplayWidth())
			{
				mCeilingBlocks[i]->setOnScreen(true);

				//Random unbiased created by "Walter" on https://stackoverflow.com/a/19728404
				std::random_device rd;     // only used once to initialise (seed) engine
				std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
				std::uniform_int_distribution<int> uni((int)(objTransform.getPosition().getY() - 30), (int)(objTransform.getPosition().getY() + 30)); // guaranteed unbiased
				auto random_integer = uni(rng);

				//if (random_integer < 150)
				//	mCeilingBlocks.push_back(new CeilingFloorBlock(objSprite, Vector2D(GraphicsSystem::getDisplayWidth(), random_integer), mVelocity));
				//else
				//	mCeilingBlocks.push_back(new CeilingFloorBlock(objSprite, Vector2D(GraphicsSystem::getDisplayWidth(), 150), mVelocity));
				mCeilingBlocks.push_back(new CeilingFloorBlock(objSprite, Vector2D(GraphicsSystem::getDisplayWidth(), 0), mVelocity));
			}
			//deletes first block on left if off screen
			else if (objTransform.getPosition().getX() + objSprite.getWidth() < 0)
			{
   				delete mCeilingBlocks.at(0);
				mCeilingBlocks.erase(mCeilingBlocks.begin());
				ceilingCount--;
				i--;
			}
		}
	}

	//loops through and updates all floor blocks
	for (int i = 0; i < floorCount; i++)
	{
		mFloorBlocks[i]->update(deltaTime);

		//checks first and last blocks
		if (i == 0 || i == mFloorBlocks.size() - 1)
		{
			const Transform& objTransform = mFloorBlocks[i]->getTransform();
			const Sprite& objSprite = mFloorBlocks[i]->getIdleSprite();

			//makes new block on right if current one is one screen
			if (!mFloorBlocks[i]->isOnScreen() && (objTransform.getPosition().getX() + objSprite.getWidth()) < GraphicsSystem::getDisplayWidth())
			{
				/*if (!mFloorBlocks[i].getOnScreen() && (mFloorBlocks[i].getBlockLoc().getX() + mFloorBlocks[i].getBlockWidth()) < mDisplayWidth)
				{*/
				mFloorBlocks[i]->setOnScreen(true);

				//Random unbiased created by "Walter" on https://stackoverflow.com/a/19728404
				std::random_device rd;     // only used once to initialise (seed) engine
				std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
				//std::uniform_int_distribution<int> uni((int)(mFloorBlocks[i].getBlockLoc().getY() - 30), (int)(mFloorBlocks[i].getBlockLoc().getY() + 30)); // guaranteed unbiased
				std::uniform_int_distribution<int> uni((int)(objTransform.getPosition().getY() - 30), (int)(objTransform.getPosition().getY() + 30)); // guaranteed unbiased
				auto random_integer = uni(rng);

  				//if (random_integer > 350)
					//mFloorBlocks.push_back(CeilingFloorBlock(mUpdateTime, mpBlockSprite, Vector2D(mDisplayWidth, random_integer)));
					//mFloorBlocks.push_back(new CeilingFloorBlock(objSprite, Vector2D(GraphicsSystem::getDisplayWidth(), random_integer), mVelocity));
				//else
					//mCeilingBlocks.push_back(CeilingFloorBlock(mUpdateTime, mpBlockSprite, Vector2D(mDisplayWidth, 350)));
					//mFloorBlocks.push_back(new CeilingFloorBlock(objSprite, Vector2D(GraphicsSystem::getDisplayWidth(), 350), mVelocity));
				//mDisplayHeight - mpBlockSprite->getHeight()
				mFloorBlocks.push_back(new CeilingFloorBlock(objSprite, Vector2D(GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight() - mCeilingFloorSprite.getHeight()), mVelocity));
			
				//handle spawning the floating wall in the middler
				mCurrentNumOfBlocksBetweenWalls--;
				if (mCurrentNumOfBlocksBetweenWalls <= 0)
				{
					spawnFloatingWall();
				}
			}
			//deletes first block on left if off screen
			//else if (mFloorBlocks[i].getBlockLoc().getX() + mFloorBlocks[i].getBlockWidth() < 0)
			else if (objTransform.getPosition().getX() + objSprite.getWidth() < 0)
			{
				delete mFloorBlocks.at(0);
				mFloorBlocks.erase(mFloorBlocks.begin());
				floorCount--;
				i--;
			}
		}
	}

	int mFloatingWallCount = mFloatingWallBlocks.size();

	for (int i = 0; i < mFloatingWallCount; i++)
	{
 		mFloatingWallBlocks[i]->update(deltaTime);

		//checks first and last blocks
		if (i == 0 || i == mFloatingWallBlocks.size() - 1)
		{
			const Transform& objTransform = mFloatingWallBlocks[i]->getTransform();
			const Sprite& objSprite = mFloatingWallBlocks[i]->getIdleSprite();

			//makes new block on right if current one is one screen
			if (!mFloatingWallBlocks[i]->isOnScreen() && (objTransform.getPosition().getX() + objSprite.getWidth()) < GraphicsSystem::getDisplayWidth())
			{
				/*if (!mFloorBlocks[i].getOnScreen() && (mFloorBlocks[i].getBlockLoc().getX() + mFloorBlocks[i].getBlockWidth()) < mDisplayWidth)
				{*/
				mFloorBlocks[i]->setOnScreen(true);
			}
			//deletes first block on left if off screen
			//else if (mFloorBlocks[i].getBlockLoc().getX() + mFloorBlocks[i].getBlockWidth() < 0)
			else if (objTransform.getPosition().getX() + objSprite.getWidth() < 0)
			{
				delete mFloatingWallBlocks.at(0);
				mFloatingWallBlocks.erase(mFloatingWallBlocks.begin());
				mFloatingWallCount--;
				i--;
			}
		}
	}
}

void CeilingFloorManager::draw()
{
	for (unsigned int i = 0; i < mCeilingBlocks.size(); i++)
	{
		mCeilingBlocks[i]->draw();
	}

	for (unsigned int i = 0; i < mFloorBlocks.size(); i++)
	{
		mFloorBlocks[i]->draw();
	}

	for (unsigned int i = 0; i < mFloatingWallBlocks.size(); i++)
	{
		mFloatingWallBlocks[i]->draw();
	}
}

void CeilingFloorManager::save()
{
	SaveManager* sm = Game::getInstance()->getSaveManager();
	SaveFile* gameSave = sm->getSaveFile("game_save_data");
	gameSave->addSaveData("num_of_ceiling_blocks", std::to_string(mCeilingBlocks.size()));
	gameSave->addSaveData("num_of_floor_blocks", std::to_string(mFloorBlocks.size()));

	for (unsigned int i = 0; i < mCeilingBlocks.size(); i++)
	{
		const Vector2D& objVelocity = mCeilingBlocks[i]->getTransform().getPosition();
		gameSave->addSaveData("ceiling_x_" + std::to_string(i), std::to_string(objVelocity.getX()));
		gameSave->addSaveData("ceiling_y_" + std::to_string(i), std::to_string(objVelocity.getY()));
	}

	for (unsigned int i = 0; i < mFloorBlocks.size(); i++)
	{
		const Vector2D& objVelocity = mFloorBlocks[i]->getTransform().getPosition();
		gameSave->addSaveData("floor_x_" + std::to_string(i), std::to_string(objVelocity.getX()));
		gameSave->addSaveData("floor_y_" + std::to_string(i), std::to_string(objVelocity.getY()));
	}
}

void CeilingFloorManager::load(SettingsFile& saveDataFile)
{
	//clears any blocks in the lists before
	cleanup();

	//finds how many blocks to add
	int numOfCeilingBlocks = std::stoi(saveDataFile.getSettingFromKey("num_of_ceiling_blocks"));
	int numOfFloorBlocks = std::stoi(saveDataFile.getSettingFromKey("num_of_floor_blocks"));

	//adds the blocks based on the saved location of each
	for (int i = 0; i < numOfCeilingBlocks; i++)
	{
		std::string nameXString = "ceiling_x_" + std::to_string(i);
		std::string nameYString = "ceiling_y_" + std::to_string(i);

		mCeilingBlocks.push_back(new CeilingFloorBlock(mCeilingFloorSprite,
			Vector2D(std::stoi(saveDataFile.getSettingFromKey(nameXString)), std::stoi(saveDataFile.getSettingFromKey(nameYString))), mVelocity));

		if (i < numOfCeilingBlocks - 1)
			mCeilingBlocks[i]->setOnScreen(true);
	}

	for (int i = 0; i < numOfFloorBlocks; i++)
	{
		std::string nameXString = "floor_x_" + std::to_string(i);
		std::string nameYString = "floor_y_" + std::to_string(i);

		mFloorBlocks.push_back(new CeilingFloorBlock(mCeilingFloorSprite,
			Vector2D(std::stoi(saveDataFile.getSettingFromKey(nameXString)), std::stoi(saveDataFile.getSettingFromKey(nameYString))), mVelocity));

		if (i < numOfFloorBlocks - 1)
			mFloorBlocks[i]->setOnScreen(true);
	}
}

void CeilingFloorManager::cleanup()
{
	for (auto blocks : mCeilingBlocks)
	{
		delete blocks;
	}

	for (auto blocks : mFloorBlocks)
	{
		delete blocks;
	}

	for(auto blocks : mFloatingWallBlocks)
	{
		delete blocks;
	}

	mCeilingBlocks.clear();
	mFloorBlocks.clear();
	mFloatingWallBlocks.clear();
}

void CeilingFloorManager::increaseSpeed()
{
	mVelocity = Vector2D(mVelocity.getX() + (float)mVelocityIncrement, mVelocity.getY());

	for (unsigned int i = 0; i < mCeilingBlocks.size(); i++)
	{
		mCeilingBlocks[i]->setVelocity(mVelocity);
	}

	for (unsigned int i = 0; i < mFloorBlocks.size(); i++)
	{
		mFloorBlocks[i]->setVelocity(mVelocity);
	}

	for (unsigned int i = 0; i < mFloatingWallBlocks.size(); i++)
	{
		mFloatingWallBlocks[i]->setVelocity(mVelocity);
	}
}

void CeilingFloorManager::spawnFloatingWall()
{
	mCurrentNumOfBlocksBetweenWalls = mNumOfBlocksBetweenWalls;

	int bottomOfCeiling = (int)mCeilingBlocks.back()->getTransform().getPosition().getY() + mCeilingBlocks.back()->getIdleSprite().getHeight();
 	int topOfFloor = (int)mFloorBlocks.back()->getTransform().getPosition().getY();

	//Random unbiased created by "Walter" on https://stackoverflow.com/a/19728404
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
							   //std::uniform_int_distribution<int> uni((int)(mFloorBlocks[i].getBlockLoc().getY() - 30), (int)(mFloorBlocks[i].getBlockLoc().getY() + 30)); // guaranteed unbiased
	std::uniform_int_distribution<int> uni((int)(bottomOfCeiling), topOfFloor - mFloatingWallSprite.getHeight()); // guaranteed unbiased
	auto random_integer = uni(rng);

	mFloatingWallBlocks.push_back(new CeilingFloorBlock(mFloatingWallSprite, Vector2D(GraphicsSystem::getDisplayWidth(), random_integer), mVelocity));
}