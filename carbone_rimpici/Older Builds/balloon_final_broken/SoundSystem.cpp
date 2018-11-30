/*#include "SoundSystem.h"
#include "Game.h"
#include "AssetManager.h"

SoundSystem::SoundSystem()
{
	
}

SoundSystem::~SoundSystem()
{
	cleanup();
}

void SoundSystem::init()
{
	balloonSound = Game::getInstance()->getAssetManager()->getSound("balloon_sound");

	mSoundList.push_back(balloonSound);
}

void SoundSystem::cleanup()
{
	for (auto sounds : mSoundList)
	{
		delete sounds;
	}

	mSoundList.clear();
}*/