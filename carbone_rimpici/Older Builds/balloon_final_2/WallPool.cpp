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

/*void WallPool::save()
{
	SaveManager* sm = Game::getInstance()->getSaveManager();
	SaveFile* gameSave = sm->getSaveFile("game_save_data");

	//need to save the velocity or acceleration of the blocks

	gameSave->addSaveData("num_of_blocks", std::to_string(mPOOL_SIZE));

	for (int i = 0; i < mPOOL_SIZE; i++)
		{
			const Vector2D& objVelocity = mpWalls[i].getTransform().getPosition();
			gameSave->addSaveData("block_x_" + std::to_string(i), std::to_string(objVelocity.getX()));
			gameSave->addSaveData("block_y_" + std::to_string(i), std::to_string(objVelocity.getY()));
		}
}

void WallPool::load(SettingsFile& saveDataFile, float acceleration, float velocity)
{
	//delete[] mpWalls;
	//mpWalls = new Wall[mPOOL_SIZE];

	//finds how many blocks to add
	int numOfBlocks = std::stoi(saveDataFile.getSettingFromKey("num_of_blocks"));

	//adds the blocks based on the saved location of each
	for (int i = 0; i < mPOOL_SIZE; i++)
	{
		std::string nameXString = "block_x_" + std::to_string(i);
		std::string nameYString = "block_y_" + std::to_string(i);

		//mCeilingBlocks.push_back(new CeilingFloorBlock(mCeilingFloorSprite,
		//	Vector2D(std::stoi(saveDataFile.getSettingFromKey(nameXString)), std::stoi(saveDataFile.getSettingFromKey(nameYString))), mVelocity));

		createWall(std::stof(saveDataFile.getSettingFromKey(nameXString)),
			std::stof(saveDataFile.getSettingFromKey(nameYString)),
			acceleration,
			velocity);

		//set blocks on screen unless their X pos is less than screen width minus sprite width
		//if (i < mPOOL_SIZE - 2)
		//	mCeilingBlocks[i]->setOnScreen(true);
	}
}*/

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