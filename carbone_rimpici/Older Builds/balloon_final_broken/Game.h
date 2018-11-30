/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef GAME_H_
#define GAME_H_

#include <Trackable.h>
#include <EventListener.h>
#include <Color.h>

class Timer;
class InputTranslator;
class Sprite;
class SettingsFile;
class Score;
class SceneManager;
class AssetManager;
class SaveManager;
//class SoundSystem;
class LocalizationMap;

class Game : public EventListener
{
public:
	static Game* getInstance();
	static bool initInstance();
	static void cleanupInstance();

	//Disable any form of copying for a Game object.
	Game(const Game& copy) = delete;
	void operator=(const Game& copy) = delete;

	bool init(const int& displayWidth, const int& displayHeight);
	void cleanup();

	void loop();

	virtual void handleEvent(const Event& theEvent);

	inline AssetManager* getAssetManager() const { return mpAssetManager; };
	inline LocalizationMap* getLocalizationMap() const { return mpLocalizationMap; };
	inline SaveManager* getSaveManager() const { return mpSaveManager; };
//	inline SoundSystem* getSoundSystem() const { return mpSoundSystem; };
	inline Vector2D getDisplayDimensions() const { return mDisplayDimensions; };
	inline SceneManager* getSceneManager() const { return mpSceneManager; }
	inline void toggleSound(bool isOn) { mIsSoundOn = isOn; };
	inline bool isSoundOn() { return mIsSoundOn; };

	void requestQuitGame();

private:
	static Game* smpInstance;
	static const int ANIMATION_SPEED_OFFSET;
	static const float mFPS;
	static const float mUPDATE_TIME;//Timer is in milliseconds
	static const float mLAG_CAP;//Timer is in milliseconds

	const std::string mDRAW_TRACKER_NAME = "draw";
	int mFrames;

	bool mIsInitialized = false;
	bool mIsLoopRunning = false;
	bool mShouldShutdown = false;
	bool mIsSoundOn = true;

	Timer* mpTimer = nullptr;

	SettingsFile* mpMainSettingsFile = nullptr;
	AssetManager* mpAssetManager = nullptr;
	LocalizationMap* mpLocalizationMap = nullptr;
	SceneManager* mpSceneManager = nullptr;
	InputTranslator* mpInputTranslator = nullptr;
	SaveManager* mpSaveManager = nullptr;
//	SoundSystem* mpSoundSystem = nullptr;

	Vector2D mDisplayDimensions;

	//Score* mpScore = nullptr;

	Game();
	~Game();

	void update(float deltaTime);
	void render();
};

#endif