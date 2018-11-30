/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "WallManager.h"
#include "Wall.h"
#include "Game.h"
#include "AssetManager.h"
#include <GraphicsSystem.h>
#include "SaveFile.h"
#include "SaveManager.h"

const std::string WallManager::ACCELERATION_ID = "horizontal";

WallManager::WallManager() :
	//Multiply by 3 because there are top walls, bottom walls, and middle walls
	mSpriteDimensions(Vector2D(Game::getInstance()->getAssetManager()->getSprite("wall_sprite")->getWidth(), Game::getInstance()->getAssetManager()->getSprite("wall_sprite")->getHeight())),
	mpWallPool(new WallPool(getAmountOfWallsFitOnScreen() * 3)),
	mIsMoving(false),
	mpWallTransform(new Transform()),
	mpHeightGenerator(new HeightGenerator())
{
	mCeilingYBaseline = -(mSpriteDimensions.getY() / 1.25f);
	mFloorYBaseline = -(mSpriteDimensions.getY() / 1.55f);
}

WallManager::~WallManager()
{
	delete mpWallPool;
	delete mpWallTransform;
	delete mpHeightGenerator;

	for (unsigned int i = 0; i < mBalloonList.size(); ++i)
	{
		delete mBalloonList.at(i);
	}

	mBalloonList.clear();
}

void WallManager::initWalls()
{
	int amountOfSpritesOnScreen = getAmountOfWallsFitOnScreen();
	
	mCeilingList.clear();

	int i;
	for (i = 0; i < amountOfSpritesOnScreen; ++i)
	{
		Wall* newWall = createWall(static_cast<float>(i * mSpriteDimensions.getX()), 
			mpHeightGenerator->getNextHeight() + mCeilingYBaseline,
			
			mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());

		if (newWall)
		{
			mCeilingList.push_back(newWall);
		}
	}

	for (i = 0; i < amountOfSpritesOnScreen; ++i)
	{
		Wall* newWall = createWall(static_cast<float>(i * mSpriteDimensions.getX()),
			mCeilingList.at(i)->getTransform().getPosition().getY() + GraphicsSystem::getDisplayHeight() - mFloorYBaseline,
			mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());

		if (newWall)
		{
			mFloorList.push_back(newWall);
		}
	}
}

void WallManager::createBalloon()
{
	int rowLength = (int)*Game::getInstance()->getAssetManager()->getValue("balloon_wall_sheet_row_amount");
	int columnLength = (int)*Game::getInstance()->getAssetManager()->getValue("balloon_wall_sheet_column_amount");
	int randomIndex = BalloonWall::getRandomBalloonIndex(rowLength, columnLength);
 	const SpriteSheet* balloonWallSpriteSheet = Game::getInstance()->getAssetManager()->getSpriteSheet("balloon_wall_spritesheet");
	Sprite* balloonWallSprite = balloonWallSpriteSheet->getSprites().at(randomIndex);

	int speed = (int)std::round(*Game::getInstance()->getAssetManager()->getValue("starting_balloon_wall_velocity"));

	int lowerBound = (int)mCeilingList.back()->getTransform().getPosition().getY() + mCeilingList.back()->getIdleSprite().getHeight();
	int upperBound = (int)mFloorList.back()->getTransform().getPosition().getY() - balloonWallSprite->getHeight();

	BalloonWall* newWall = new BalloonWall(*balloonWallSpriteSheet, randomIndex, lowerBound, upperBound, speed);
	newWall->init((float)GraphicsSystem::getDisplayWidth(), (float)HeightGenerator::getRandomInt(lowerBound, upperBound), mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());
	
	mBalloonList.push_back(newWall);
}

void WallManager::createBalloon(float x, float y, int speed)
{
	int rowLength = (int)*Game::getInstance()->getAssetManager()->getValue("balloon_wall_sheet_row_amount");
	int columnLength = (int)*Game::getInstance()->getAssetManager()->getValue("balloon_wall_sheet_column_amount");
	int randomIndex = BalloonWall::getRandomBalloonIndex(rowLength, columnLength);
	createBalloon(randomIndex, x, y, speed);
}

void WallManager::createBalloon(int spriteIndex, float x, float y, int speed)
{
	SpriteSheet* balloonWallSpriteSheet = Game::getInstance()->getAssetManager()->getSpriteSheet("balloon_wall_spritesheet");
	Sprite* balloonWallSprite = balloonWallSpriteSheet->getSprites().at(spriteIndex);

	int lowerBound = (int)mCeilingList.back()->getTransform().getPosition().getY() + mCeilingList.back()->getIdleSprite().getHeight() + 50;
	int upperBound = (int)mFloorList.back()->getTransform().getPosition().getY() - balloonWallSprite->getHeight() - 50;

	BalloonWall* newWall = new BalloonWall(*balloonWallSpriteSheet, spriteIndex, lowerBound, upperBound, speed);
	newWall->init(x, y, mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());

	mBalloonList.push_back(newWall);
}

void WallManager::deleteBalloon(unsigned int balloonIndex)
{
	if (balloonIndex < mBalloonList.size())
	{
		BalloonWall* wall = mBalloonList.at(balloonIndex);
		mBalloonList.erase(mBalloonList.begin() + balloonIndex);
		delete wall;
	}
}

void WallManager::update(float deltaTime)
{
	for (unsigned int i = 0; i < mBalloonList.size(); ++i)
	{
		BalloonWall* currentBalloon = mBalloonList.at(i);
		currentBalloon->update(deltaTime);

		if (!currentBalloon->isOnScreen())
		{
			deleteBalloon(i);
		}
		else if (isWallCollidingWith(currentBalloon->mpBounds) && currentBalloon->getCoolDown() <= 0)
		{
			currentBalloon->invertSpeed();
			currentBalloon->resetCoolDown();
		}
	}

	for (unsigned int i = 0; i < mCeilingList.size(); ++i)
	{
		if (!mCeilingList.at(i)->isInUse())
		{
			Wall* newCeilingWall = createWall(mCeilingList.at(mCeilingList.size() - 1)->getTransform().getPosition().getX() + mSpriteDimensions.getX(),
				mpHeightGenerator->getNextHeight() + mCeilingYBaseline,
				mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());

			Wall* newFloorWall = createWall(mFloorList.at(mFloorList.size() - 1)->getTransform().getPosition().getX() + mSpriteDimensions.getX(),
				newCeilingWall->getTransform().getPosition().getY() + GraphicsSystem::getDisplayHeight() - mFloorYBaseline,
				mpWallTransform->getAcceleration().getX(), mpWallTransform->getVelocity().getX());

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

	mTimeTilBalloonSpawn -= deltaTime;

	if (mTimeTilBalloonSpawn <= 0)
	{
		mTimeTilBalloonSpawn = 5000;
		createBalloon();
	}

	mpWallTransform->update(deltaTime);
	mpWallPool->update(deltaTime);
}

void WallManager::draw()
{
	for (unsigned int i = 0; i < mBalloonList.size(); ++i)
	{
		mBalloonList.at(i)->draw();
	}

	mpWallPool->draw();
}

void WallManager::save()
{
	SaveManager* sm = Game::getInstance()->getSaveManager();
	SaveFile* gameSave = sm->getSaveFile("game_save_data");

	gameSave->addSaveData("wall_acceleration", std::to_string(mpWallTransform->getAcceleration().getX()));
	gameSave->addSaveData("wall_velocity", std::to_string(mpWallTransform->getVelocity().getX()));
	gameSave->addSaveData("time_till_next_balloon_spawn", std::to_string(mTimeTilBalloonSpawn));

	gameSave->addSaveData("num_of_ceiling_blocks", std::to_string(mCeilingList.size()));
	gameSave->addSaveData("num_of_floor_blocks", std::to_string(mFloorList.size()));
	gameSave->addSaveData("num_of_balloon_blocks", std::to_string(mBalloonList.size()));

	gameSave->addSaveData("wall_difficulty_frequency", std::to_string(mpHeightGenerator->getFrequency()));
	gameSave->addSaveData("wall_difficulty_amplitude", std::to_string(mpHeightGenerator->getAmplitude()));
	gameSave->addSaveData("wall_difficulty_generation_time", std::to_string(mpHeightGenerator->getTime()));

	for (unsigned int i = 0; i < mCeilingList.size(); i++)
	{
		const Vector2D& objPosition = mCeilingList[i]->getTransform().getPosition();
		gameSave->addSaveData("ceiling_x_" + std::to_string(i), std::to_string(objPosition.getX()));
		gameSave->addSaveData("ceiling_y_" + std::to_string(i), std::to_string(objPosition.getY()));
	}

	for (unsigned int i = 0; i < mFloorList.size(); i++)
	{
		const Vector2D& objPosition = mFloorList[i]->getTransform().getPosition();
		gameSave->addSaveData("floor_x_" + std::to_string(i), std::to_string(objPosition.getX()));
		gameSave->addSaveData("floor_y_" + std::to_string(i), std::to_string(objPosition.getY()));
	}

	for (unsigned int i = 0; i < mBalloonList.size(); ++i)
	{
		const Vector2D& objPosition = mBalloonList[i]->getTransform().getPosition();
		gameSave->addSaveData("balloon_x_" + std::to_string(i), std::to_string(objPosition.getX()));
		gameSave->addSaveData("balloon_y_" + std::to_string(i), std::to_string(objPosition.getY()));
		gameSave->addSaveData("balloon_color_index_" + std::to_string(i), std::to_string(mBalloonList[i]->getSpriteSheetIndex()));
		gameSave->addSaveData("balloon_speed_" + std::to_string(i), std::to_string(mBalloonList[i]->getSpeed()));
	}
}

void WallManager::initNewGame()
{
 	mTimeTilBalloonSpawn = 1000;

	mpWallTransform->reset();
	mpWallTransform->setAcceleration(ACCELERATION_ID, static_cast<float>(*Game::getInstance()->getAssetManager()->getValue("starting_acceleration_x")), 0.0f);
	mpWallTransform->setVelocity(static_cast<float>(*Game::getInstance()->getAssetManager()->getValue("starting_velocity_x")), 0.0f);

	mpHeightGenerator->setMinHeightOffset(-mSpriteDimensions.getY() * 2);
	mpHeightGenerator->setMaxHeightOffset(mSpriteDimensions.getY() * 2);
	mpHeightGenerator->setFrequency(40.0f);
	mpHeightGenerator->setAmplitude(1.0f);

	initWalls();
}

void WallManager::load(SettingsFile& saveDataFile)
{
	//need to set the saved velocity and acceleration
	mpWallTransform->reset();
	mpWallTransform->setAcceleration(ACCELERATION_ID, std::stof(saveDataFile.getSettingFromKey("wall_acceleration")), 0.0f);
	mpWallTransform->setVelocity(std::stof(saveDataFile.getSettingFromKey("wall_velocity")), 0.0f);
	
	//init wall and balloon variables
	mTimeTilBalloonSpawn = std::stof(saveDataFile.getSettingFromKey("time_till_next_balloon_spawn"));

	float frequency = std::stof(saveDataFile.getSettingFromKey("wall_difficulty_frequency"));
	float amplitude = std::stof(saveDataFile.getSettingFromKey("wall_difficulty_amplitude"));
	float genTimeCounter = std::stof(saveDataFile.getSettingFromKey("wall_difficulty_generation_time"));

	//finds how many blocks to add
	int numOfCeilingBlocks = std::stoi(saveDataFile.getSettingFromKey("num_of_ceiling_blocks"));
	int numOfFloorBlocks = std::stoi(saveDataFile.getSettingFromKey("num_of_floor_blocks"));
	int numOfBalloonBlocks = std::stoi(saveDataFile.getSettingFromKey("num_of_balloon_blocks"));

	float acceleration = mpWallTransform->getAcceleration().getX();
	float velocity = mpWallTransform->getVelocity().getX();

	mpHeightGenerator->setMinHeightOffset(-mSpriteDimensions.getY());
	mpHeightGenerator->setMaxHeightOffset(mSpriteDimensions.getY());
	mpHeightGenerator->setTime(genTimeCounter);
	mpHeightGenerator->setFrequency(frequency);
	mpHeightGenerator->setAmplitude(amplitude);

	//adds the blocks based on the saved location of each
	for (int i = 0; i < numOfCeilingBlocks; i++)
	{
		std::string positionX = "ceiling_x_" + std::to_string(i);
		std::string positionY = "ceiling_y_" + std::to_string(i);

		Wall* newWall = mpWallPool->createWall(std::stof(saveDataFile.getSettingFromKey(positionX)),
			std::stof(saveDataFile.getSettingFromKey(positionY)),
			acceleration,
			velocity);

		mCeilingList.push_back(newWall);
	}

	for (int i = 0; i < numOfFloorBlocks; i++)
	{
		std::string positionX = "floor_x_" + std::to_string(i);
		std::string positionY = "floor_y_" + std::to_string(i);

		Wall* newWall = mpWallPool->createWall(std::stof(saveDataFile.getSettingFromKey(positionX)),
			std::stof(saveDataFile.getSettingFromKey(positionY)),
			acceleration,
			velocity);

		mFloorList.push_back(newWall);
	}

	for (int i = 0; i < numOfBalloonBlocks; i++)
	{
		std::string positionX = "balloon_x_" + std::to_string(i);
		std::string positionY = "balloon_y_" + std::to_string(i);
		std::string balloonSpriteIndex = "balloon_color_index_" + std::to_string(i);
		std::string balloonSpeed = "balloon_speed_" + std::to_string(i);

		createBalloon(std::stoi(saveDataFile.getSettingFromKey(balloonSpriteIndex)), std::stof(saveDataFile.getSettingFromKey(positionX)), std::stof(saveDataFile.getSettingFromKey(positionY)), std::stoi(saveDataFile.getSettingFromKey(balloonSpeed)));
	}
}

int WallManager::getAmountOfWallsFitOnScreen()
{
	return static_cast<int>((GraphicsSystem::getInstance()->getDisplayWidth() / mSpriteDimensions.getX())) + 2;
}

Wall* WallManager::createWall(float x, float y, float acceleration, float velocity)
{
	return mpWallPool->createWall(x, y, acceleration, velocity);
}

bool WallManager::isWallCollidingWith(RectBounds* bounds)
{
	return mpWallPool->checkCollision(bounds);
}

bool WallManager::isBalloonCollidingWith(RectBounds* bounds)
{
	for (unsigned int i = 0; i < mBalloonList.size(); ++i)
	{
		if (mBalloonList.at(i)->mpBounds->isIntersecting(bounds))
		{
			return true;
		}
	}

	return false;
}