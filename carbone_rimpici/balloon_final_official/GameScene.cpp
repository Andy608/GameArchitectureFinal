/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <GraphicsSystem.h>
#include "GameScene.h"
#include "Game.h"
#include "AssetManager.h"
#include "Player.h"
#include "Score.h"
#include "WallManager.h"
#include "SaveManager.h"
#include "SettingsFile.h"
#include "SceneManager.h"

#include <cmath>

void GameScene::start()
{
	try
	{
		Game::getInstance()->resetScore();

		mpPlayer = new Player(*Game::getInstance()->getAssetManager()->getSprite("player_sprite"));
		
		mpWallManager = new WallManager();

		mpScore = new Score(mpAssetManagerInstance->getFont("gui_font"),
			mpAssetManagerInstance->getColor("text_color"),
			*mpAssetManagerInstance->getValue("score_update_timing"),
			(int)*mpAssetManagerInstance->getValue("score_difficulty_change"),
			*mpAssetManagerInstance->getVector2D("score_location"));
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
	else
	{
		setupNewGame();
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
	
	if (mpWallManager)
	{
		delete mpWallManager;
		mpWallManager = nullptr;
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
	mpWallManager->update(deltaTime);
	mpScore->update(deltaTime);

	difficultyCheck();
	checkCollision();
}

void GameScene::draw()
{
	GraphicsSystem::drawScaledToFit(0, 0, *mpAssetManagerInstance->getBuffer("background_buffer"), GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
	mpPlayer->draw();
	mpWallManager->draw();
	mpScore->draw();
}

void GameScene::save()
{
	mpPlayer->save();
	mpWallManager->save();
	mpScore->save();
}

void GameScene::load()
{
	SaveFile* saveDataFile = Game::getInstance()->getSaveManager()->getSaveFile("game_save_data");
	mpPlayer->load(*saveDataFile);
	mpWallManager->load(*saveDataFile);
	mpScore->load(*saveDataFile);
}

void GameScene::checkCollision()
{
	if (mpWallManager->isWallCollidingWith(mpPlayer->getRectBounds()) ||
		mpWallManager->isBalloonCollidingWith(mpPlayer->getRectBounds()))
	{
		std::cout << "Touching wall" << std::endl;

		endGame();
		return;
	}
}

void GameScene::setupNewGame()
{
	mpWallManager->initNewGame();
}

void GameScene::difficultyCheck()
{
	if (mpScore->getDifficultyTracking() >= mpScore->getScoreDifficultyChange())
	{
		//Increase difficulty
		float frequency = mpWallManager->mpHeightGenerator->getFrequency();
		float amplitude = mpWallManager->mpHeightGenerator->getAmplitude();
		mpWallManager->mpHeightGenerator->setFrequency(frequency * *Game::getInstance()->getAssetManager()->getValue("difficulty_frequency_scale"));
		mpWallManager->mpHeightGenerator->setAmplitude(amplitude * *Game::getInstance()->getAssetManager()->getValue("difficulty_amplitude_scale"));
		
		mpScore->resetScoreDifficultyTracking();
	}
}

void GameScene::endGame()
{
	if (Game::getInstance()->isSoundOn())
	{
		Game::getInstance()->getSaveManager()->getSaveFile("game_save_data")->deleteSaveData();
		Game::getInstance()->getAssetManager()->getSound("balloon_sound")->fadeOutSound(500);
	}

	Game::getInstance()->setScore(mpScore->getScore());
	Game::getInstance()->getSceneManager()->setCurrentScene(EnumScene::END_SCENE);
}