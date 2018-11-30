#include <GraphicsSystem.h>
#include "GameScene.h"
#include "Game.h"
#include "AssetManager.h"
#include "Player.h"
#include "Score.h"
#include "CeilingFloorManager.h"
#include "SaveManager.h"
#include "SettingsFile.h"
#include "SceneManager.h"

#include <cmath>

void GameScene::start()
{
	try
	{
		mpPlayer = new Player(*Game::getInstance()->getAssetManager()->getSprite("player_sprite"));
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}

	try
	{
		AssetManager* theAssetManager = Game::getInstance()->getAssetManager();
		mpCFManager = new CeilingFloorManager(*theAssetManager->getSprite("wall_sprite"),
			*theAssetManager->getSprite("floating_wall_sprite"),
			*theAssetManager->getValue("difficulty_block_initial_velocity"),
			*theAssetManager->getValue("difficulty_block_increment_velocity"));
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
	}

	try
	{
		AssetManager* theAssetManager = Game::getInstance()->getAssetManager();
		mpScore = new Score(theAssetManager->getFont("gui_font"),
			theAssetManager->getColor("text_color"),
			*theAssetManager->getValue("score_update_timing"),
			(int)*theAssetManager->getValue("score_difficulty_change"),
			*theAssetManager->getVector2D("score_location"));
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
		cleanup();
	}

	if (!Game::getInstance()->getSaveManager()->getSaveFile("game_save_data")->isEmpty())
	{
		load();
	}

	mIsInitialized = true;
}

void GameScene::end()
{
	cleanup();
}

void GameScene::cleanup()
{
	if (mpPlayer)
	{
		delete mpPlayer;
		mpPlayer = nullptr;
	}
	
	if (mpCFManager)
	{
		delete mpCFManager;
		mpCFManager = nullptr;
	}

	if (mpScore)
	{
		delete mpScore;
		mpScore = nullptr;
	}

	mIsInitialized = false;
}

void GameScene::update(float deltaTime)
{
	mpPlayer->update(deltaTime);
	mpCFManager->update(deltaTime);
	mpScore->update(deltaTime);

	difficultyCheck();
	checkCollision();
}

void GameScene::draw()
{
	AssetManager* assetManager = Game::getInstance()->getAssetManager();
	GraphicsSystem::drawScaledToFit(0, 0, *assetManager->getBuffer("background_buffer"), GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
	mpPlayer->draw();
	mpCFManager->draw();
	mpScore->draw();
}

void GameScene::save()
{
	//call SaveManager function that adds stuff to save to a list
	mpPlayer->save();
	mpCFManager->save();
	mpScore->save();
}

void GameScene::load()
{
	SaveFile* saveDataFile = Game::getInstance()->getSaveManager()->getSaveFile("game_save_data");
	mpPlayer->load(*saveDataFile);
	mpCFManager->load(*saveDataFile);
	mpScore->load(*saveDataFile);
}

void GameScene::checkCollision()
{
	int playerLeftBound = (int)mpPlayer->getTransform().getPosition().getX();
	int playerRightBound = playerLeftBound + mpPlayer->getIdleSprite().getWidth();
	int playerTopBound = (int)mpPlayer->getTransform().getPosition().getY();
	int playerBottomBound = playerTopBound - mpPlayer->getIdleSprite().getHeight();

 	int blockHeight = mpCFManager->mCeilingFloorSprite.getHeight();
	int blockWidth = mpCFManager->mCeilingFloorSprite.getWidth();

	if (playerBottomBound >= 0)
 		std::cout << "Test" << std::endl;


	for (unsigned int j = 0; j < mpCFManager->mCeilingBlocks.size(); j++)
	{
		int blockLeftBound = (int)mpCFManager->mCeilingBlocks[j]->getTransform().getPosition().getX();
		int blockRightBound = blockLeftBound + blockWidth;
		int blockTopBound = (int)mpCFManager->mCeilingBlocks[j]->getTransform().getPosition().getY() * -1;
		int blockBottomBound = blockTopBound - blockHeight;

 		if ((playerLeftBound >= blockLeftBound && playerLeftBound <= blockRightBound) ||
			(playerRightBound >= blockLeftBound && playerRightBound <= blockRightBound))
		{
			if ((playerTopBound <= blockTopBound && playerTopBound >= blockBottomBound) ||
				(playerBottomBound <= blockTopBound && playerBottomBound >= blockBottomBound))
			{
				std::cout << "Touching ceiling" << std::endl;
				endGame();
				return;
			}
		}
	}

	for (unsigned int j = 0; j < mpCFManager->mFloorBlocks.size(); j++)
	{
		int blockLeftBound2 = (int)mpCFManager->mFloorBlocks[j]->getTransform().getPosition().getX();
		int blockRightBound2 = blockLeftBound2 + blockWidth;
		int blockTopBound2 = (int)mpCFManager->mFloorBlocks[j]->getTransform().getPosition().getY() * -1;
		int blockBottomBound2 = blockTopBound2 - blockHeight;

		if ((playerLeftBound >= blockLeftBound2 && playerLeftBound <= blockRightBound2) ||
			(playerRightBound >= blockLeftBound2 && playerRightBound <= blockRightBound2))
		{
			if ((playerTopBound <= blockTopBound2 && playerTopBound >= blockBottomBound2) ||
				(playerBottomBound <= blockTopBound2 && playerBottomBound >= blockBottomBound2))
			{
				std::cout << "Touching floor" << std::endl;
				endGame();
				return;
			}
		}
	}

	blockHeight = mpCFManager->mFloatingWallSprite.getHeight();
	blockWidth = mpCFManager->mFloatingWallSprite.getWidth();

	for (unsigned int j = 0; j < mpCFManager->mFloatingWallBlocks.size(); j++)
	{
		int blockLeftBound2 = (int)mpCFManager->mFloatingWallBlocks[j]->getTransform().getPosition().getX();
		int blockRightBound2 = blockLeftBound2 + blockWidth;
		int blockTopBound2 = (int)mpCFManager->mFloatingWallBlocks[j]->getTransform().getPosition().getY() * -1;
		int blockBottomBound2 = blockTopBound2 - blockHeight;

		if ((playerLeftBound >= blockLeftBound2 && playerLeftBound <= blockRightBound2) ||
			(playerRightBound >= blockLeftBound2 && playerRightBound <= blockRightBound2))
		{
			if ((playerTopBound <= blockTopBound2 && playerTopBound >= blockBottomBound2) ||
				(playerBottomBound <= blockTopBound2 && playerBottomBound >= blockBottomBound2))
			{
				std::cout << "Touching wall" << std::endl;
				endGame();
				return;
			}
		}
	}
}

void GameScene::difficultyCheck()
{
	if (mpScore->getDifficultyTracking() >= mpScore->getScoreDifficultyChange())
	{
 		mpCFManager->increaseSpeed();
		mpScore->resetScoreDifficultyTracking();
	}
}

void GameScene::endGame()
{
	//Call sound manager and turn off all sounds
	Game::getInstance()->getSceneManager()->setCurrentScene(EnumScene::TITLE_SCENE);
}