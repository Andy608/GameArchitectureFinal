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
	try
	{
		return mAnimationContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

GraphicsBuffer* AssetManager::getBuffer(std::string key) const
{
	try
	{
		return mBufferContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Sprite* AssetManager::getSprite(std::string key) const
{
	try
	{
		return mSpriteContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

SpriteSheet* AssetManager::getSpriteSheet(std::string key) const
{
	try
	{
		return mSpriteSheetContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
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
			std::cout << "Unable to load asset from file. Error: " << e.what() << std::endl;
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
	mBufferContainer.addAsset("background_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("background_buffer")));
	mBufferContainer.addAsset("air_balloon", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("air_balloon_buffer")));
}

void AssetManager::loadSprites()
{
	mSpriteContainer.addAsset("player_sprite", new Sprite(*mBufferContainer.getAsset("air_balloon")));
}

void AssetManager::loadSpriteSheets()
{

}