#include "Sound.h"

Sound::Sound(std::string filename, bool isSoundEffect) :
	mChannel(-1),
	mIsSoundEffect(isSoundEffect)
{
	if (isSoundEffect)
	{
		mSound = Mix_LoadWAV(filename.c_str());
	}
	else
	{
		mMusic = Mix_LoadMUS(filename.c_str());
	}
}

Sound::~Sound()
{
	if (mIsSoundEffect)
	{
		Mix_FreeChunk(mSound);
		mSound = nullptr;
	}
	else
	{
		Mix_FreeMusic(mMusic);
		mMusic = nullptr;
	}
}

void Sound::fadeInSound(int fadeInMillis)
{
	//mChannel = Mix_PlayChannel(-1, mSound, -1);
	if (mIsSoundEffect)
		mChannel = Mix_FadeInChannel(-1, mSound, -1, fadeInMillis);
	else
		//Mix_FadeInMusic(mMusic, -1, fadeInMillis);
	{
		Mix_PlayMusic(mMusic, -1);
		Mix_VolumeMusic(20);
	}
}

void Sound::fadeOutSound(int fadeOutMillis)
{
	//Mix_HaltChannel(mChannel);
	if (mIsSoundEffect)
		Mix_FadeOutChannel(mChannel, fadeOutMillis);
	else
		Mix_FadeOutMusic(fadeOutMillis);
}

bool Sound::isPlaying()
{
	if (mIsSoundEffect)
		return Mix_Playing(mChannel);
	else
		return Mix_PlayingMusic();
}