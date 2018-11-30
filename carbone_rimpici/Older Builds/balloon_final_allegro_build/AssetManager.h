#ifndef ASSET_MANAGER_H_
#define ASSET_MANAGER_H_

#include <Trackable.h>
#include <map>
#include <string>
#include "SettingsFile.h"
#include "AssetContainer.h"

class Sprite;
class SpriteSheet;
class Animation;
class GraphicsBuffer;

class AssetManager : public Trackable
{
public:
	AssetManager(SettingsFile& mainSettingsFile);
	~AssetManager();

	bool loadAssets();

	Animation* getAnimation(std::string key) const;
	GraphicsBuffer* getBuffer(std::string key) const;
	Sprite* getSprite(std::string key) const;
	SpriteSheet* getSpriteSheet(std::string key) const;
	//const Sound* getSound(std::string key) const;
	//const Music* getMusic(std::string key) const;

private:
	bool mIsLoaded;

	SettingsFile& mMainSettingsFile;

	//Going to hold lists of...
	//Animations
	AssetContainer<Animation> mAnimationContainer;
	
	//Buffers
	AssetContainer<GraphicsBuffer> mBufferContainer;
	
	//Sprites
	AssetContainer<Sprite> mSpriteContainer;

	//Spritesheets
	AssetContainer<SpriteSheet> mSpriteSheetContainer;

	//Sounds
	//To be implemented

	//Music
	//To be implemented

	void loadAnimations();
	void loadBuffers();
	void loadSprites();
	void loadSpriteSheets();
};

#endif