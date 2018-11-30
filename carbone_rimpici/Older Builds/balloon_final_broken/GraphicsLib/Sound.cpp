#include "Sound.h"

Sound::Sound(std::string filename) : 
	mSound(Mix_LoadWAV(filename.c_str())),
	mChannel(-1)
{
	
}

Sound::~Sound()
{
	Mix_FreeChunk(mSound);
}

void Sound::fadeInSound(int fadeInMillis)
{
	//mChannel = Mix_PlayChannel(-1, mSound, -1);
	mChannel = Mix_FadeInChannel(-1, mSound, -1, fadeInMillis);
}

void Sound::fadeOutSound(int fadeOutMillis)
{
	//Mix_HaltChannel(mChannel);
	Mix_FadeOutChannel(mChannel, fadeOutMillis);
}

bool Sound::isPlaying()
{
	return Mix_Playing(mChannel);
}