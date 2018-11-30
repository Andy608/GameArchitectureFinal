/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

//External Includes
#include <assert.h>
#include <Timer.h>
#include <PerformanceTracker.h>

//Graphics Lib Includes
#include <System.h>
#include <EventSystem.h>
#include <Font.h>
#include <SpriteSheet.h>
#include <Animation.h>
#include <Event.h>

//Balloon Final Includes
#include "Game.h"
#include "InputTranslator.h"
#include "SettingsFile.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "LocalizationMap.h"
#include "SaveManager.h"
#include "SoundSystem.h"
#include "Score.h"

//Temp
#include "Player.h"

Game* Game::smpInstance = nullptr;

const int Game::ANIMATION_SPEED_OFFSET = 10;
const float Game::mFPS = 60.0f;
const float Game::mUPDATE_TIME = (1.0f / mFPS) * 1000.0f;	//Timer is in milliseconds
const float Game::mLAG_CAP = 0.15f * 1000.0f;				//Timer is in milliseconds

Game* Game::getInstance()
{
	assert(smpInstance);
	return smpInstance;
}

bool Game::initInstance()
{
	if (!smpInstance)
	{
		std::cout << "Game instance is null, creating new instance." << std::endl;
		smpInstance = new Game();
	}

	return smpInstance;
}

void Game::cleanupInstance()
{
	delete smpInstance;
	smpInstance = nullptr;
}

Game::Game() : EventListener(EventSystem::getInstance())
{
	EventSystem::addListener(Event::EnumEventType::_INPUT_EVENT, this);
	EventSystem::addListener(Event::EnumEventType::_QUIT_EVENT, this);
}

Game::~Game()
{
	cleanup();
}

bool Game::init(const int& displayWidth, const int& displayHeight)
{
	if (!mIsInitialized)
	{
		mpTimer = new Timer();

		mIsInitialized = true;

		if (System::initInstance(displayWidth, displayHeight))
		{
			mDisplayDimensions = Vector2D(displayHeight, displayWidth);

			mpInputTranslator = new InputTranslator();

			mpMainSettingsFile = new SettingsFile("assets/data_files/game_data.txt");
			mpAssetManager = new AssetManager(*mpMainSettingsFile);
			mpLocalizationMap = new LocalizationMap();

			mpSceneManager = new SceneManager();

			mpSaveManager = new SaveManager();
			mpSaveManager->addSaveFile("game_save_data", "assets/data_files/game_save_data.txt");
			mpSaveManager->addSaveFile("options_save_data", "assets/data_files/options_save_data.txt");

			if (!mpLocalizationMap->initLangauges(*mpMainSettingsFile))
			{
				std::cout << "Error loading languages." << std::endl;
				cleanup();
			}
			else if (!mpAssetManager->loadAssets())
			{
				std::cout << "Error loading assets." << std::endl;
				cleanup();
			}
			else if (!mpInputTranslator->init())
			{
				std::cout << "Error initializing Input Translator." << std::endl;
				cleanup();
			}

			//mpSoundSystem = new SoundSystem();
			//mpSoundSystem->init();

			/*try
			{
				//Font* tempFont = new Font("assets/font/SigmarOne-Regular.ttf", 45);
				//Color* tempColor = new Color(255, 0, 0);
				mpScore = new Score(tempFont, mpAssetManager->getColor("text_color"), 0.3, Vector2D(25,25));
			}
			catch (const std::exception& e)
			{
				std::cout << "ERROR: " << e.what() << std::endl;
				cleanup();
			}*/

			mpSceneManager->initScenes();
		}
		else
		{
			std::cout << "Error initializing System." << std::endl;
			cleanup();
		}
	}

	return mIsInitialized;
}

void Game::cleanup()
{
	if (mIsInitialized )
	{
		EventSystem::getInstance()->removeListener(Event::EnumEventType::_INPUT_EVENT, this);
		EventSystem::getInstance()->removeListener(Event::EnumEventType::_QUIT_EVENT, this);

		if (mpSceneManager)
		{
			delete mpSceneManager;
		}

		if (mpSaveManager)
		{
			mpSaveManager->saveAllData();

			delete mpSaveManager;
			mpSaveManager = nullptr;
		}

		if (mpMainSettingsFile)
		{
			delete mpMainSettingsFile;
			mpMainSettingsFile = nullptr;
		}

		if (mpAssetManager)
		{
			delete mpAssetManager;
			mpAssetManager = nullptr;
		}

		if (mpLocalizationMap)
		{
			delete mpLocalizationMap;
			mpLocalizationMap = nullptr;
		}

		if (mpInputTranslator)
		{
			delete mpInputTranslator;
			mpInputTranslator = nullptr;
		}

		if (mpTimer)
		{
			delete mpTimer;
			mpTimer = nullptr;
		}

		/*if (mpSoundSystem)
		{
			delete mpSoundSystem;
		}*/

		System::cleanupInstance();

		mIsInitialized = false;
		mIsLoopRunning = false;
	}
}

void Game::loop()
{
	if (!mIsInitialized)
	{
		std::cout << "The game is not initialized yet." << std::endl;
	}
	else if (mIsLoopRunning)
	{
		std::cout << "The game loop is already running." << std::endl;
	}
	else
	{
		//Start the loop
		mIsLoopRunning = true;
		
		mpTimer->start();

		PerformanceTracker* pPerformanceTracker = new PerformanceTracker;
		pPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);

		while (!mShouldShutdown)
		{
			pPerformanceTracker->clearTracker(mDRAW_TRACKER_NAME);
			pPerformanceTracker->startTracking(mDRAW_TRACKER_NAME);
			mpTimer->start();

			//Update and render
			update(mUPDATE_TIME);
			render();

			mpTimer->sleepUntilElapsed(mUPDATE_TIME);
			pPerformanceTracker->stopTracking(mDRAW_TRACKER_NAME);

			//Print out the frames to the console
			mFrames = static_cast<int>(round(1000.0f / pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME)));
			//std::cout << "Elapsed Time: " << pPerformanceTracker->getElapsedTime(mDRAW_TRACKER_NAME) << " milliseconds" << std::endl;
		}

		mIsLoopRunning = false;

		delete pPerformanceTracker;
	}
}

void Game::update(float deltaTime)
{
	System::getInstance()->getInputSystem()->update(deltaTime);
	mpSceneManager->update(deltaTime);
	//mpTestPlayer->update(deltaTime);
	//mpScore->update(deltaTime);
}

void Game::render()
{
	try
	{
		mpSceneManager->draw();
		//GraphicsSystem::drawScaledToFit(0, 0, *mpAssetManager->getBuffer("background_buffer"), GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
		//mpTestPlayer->draw();
		//mpScore->draw();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	GraphicsSystem::flip();
}

void Game::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case Event::EnumEventType::_QUIT_EVENT:
		requestQuitGame();
		break;
	case Event::EnumEventType::_INPUT_EVENT:
		const KeyboardEvent& inputEvent = static_cast<const KeyboardEvent&>(theEvent);

		/*if (inputEvent.isKeyDown() && inputEvent.getInputCode() == EnumKeyInput::ENTER_KEY)
		{
			mpSceneManager->setCurrentScene(static_cast<EnumScene>((static_cast<int>(
				mpSceneManager->getCurrentSceneType()) + 1) % (EnumScene::NUM_SCENE_TYPES - 1)
			));
		}
		else*/
		/*if (inputEvent.isKeyDown() && inputEvent.getInputCode() == EnumKeyInput::L_KEY)
		{
			mpLocalizationMap->setCurrentLanguage(static_cast<EnumLanguage>(((int)mpLocalizationMap->getLanguageType() + 1) % EnumLanguage::LANGUAGE_COUNT));
			EventSystem::fireEvent(LanguageChangedEvent());
		}*/
	}
}

void Game::requestQuitGame()
{
	mShouldShutdown = true;
}