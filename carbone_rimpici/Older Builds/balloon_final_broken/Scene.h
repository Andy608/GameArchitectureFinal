#ifndef SCENE_H_
#define SCENE_H_

#include <Trackable.h>
#include "Game.h"

enum EnumScene : int
{
	TITLE_SCENE,
	GAME_SCENE,
	OPTIONS_SCENE,
	END_SCENE,
	NUM_SCENE_TYPES
};

class AssetManager;
class LocalizationMap;

//Scene
class Scene
{
public:
	friend class SceneManager;

	virtual void start() = 0;
	virtual void end() = 0;
	virtual void cleanup() = 0;

	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void save() = 0;
	virtual void load() = 0;


	inline EnumScene getSceneType() const { return mSceneType; };

protected:
	Game* mpGameInstance;
	LocalizationMap* mpLocalizationInstance;
	AssetManager* mpAssetManagerInstance;

	EnumScene mSceneType;
	bool mIsInitialized;

	inline Scene(EnumScene sceneType) 
	{ 
		mSceneType = sceneType;
		mpGameInstance = Game::getInstance();
		mpLocalizationInstance = Game::getInstance()->getLocalizationMap();
		mpAssetManagerInstance = Game::getInstance()->getAssetManager();
	};

	virtual inline ~Scene() {};
};

#endif