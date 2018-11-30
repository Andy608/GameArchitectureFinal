#include "AssetManager.h"
#include "SettingsFile.h"
#include <Sprite.h>
#include <SpriteSheet.h>
#include <Animation.h>
#include <GraphicsBuffer.h>

AssetManager::AssetManager(SettingsFile& mainSettingsFile) :
	mMainSettingsFile(mainSettingsFile),
	mIsLoaded(false)
{

}

AssetManager::~AssetManager()
{
	mAnimationContainer.clearAssets();
	mBufferContainer.clearAssets();
	mSpriteContainer.clearAssets();
	mSpriteSheetContainer.clearAssets();
}

Animation* AssetManager::getAnimation(std::string key) const
{
	return mAnimationContainer.getAsset(key);
}

GraphicsBuffer* AssetManager::getBuffer(std::string key) const
{
	return mBufferContainer.getAsset(key);
}

Sprite* AssetManager::getSprite(std::string key) const
{
	return mSpriteContainer.getAsset(key);
}

SpriteSheet* AssetManager::getSpriteSheet(std::string key) const
{
	return mSpriteSheetContainer.getAsset(key);
}

bool AssetManager::loadAssets()
{
	bool success;

	if (!mIsLoaded)
	{
		try
		{
			loadBuffers();
			loadSprites();
			loadSpriteSheets();
			loadAnimations();
			success = true;
		}
		catch (const std::exception& e)
		{
			success = false;
			std::cout << "Unable to load asset from file. Error: \'" << e.what() << "\'" << std::endl;
		}

		if (success)
		{
			mIsLoaded = true;
		}
	}

	return success;
}

void AssetManager::loadAnimations()
{
	//throw std::exception("Testing");
}

void AssetManager::loadBuffers()
{
	mBufferContainer.addAsset("background_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("background_sprite")));
	mBufferContainer.addAsset("balloon_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("balloon_sprite")));
}

void AssetManager::loadSprites()
{

}

void AssetManager::loadSpriteSheets()
{

}