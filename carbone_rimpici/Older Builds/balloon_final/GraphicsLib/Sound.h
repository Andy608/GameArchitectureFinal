#ifndef SOUND_H_
#define SOUND_H_

#include <Trackable.h>
#include <SDL.h>
#include <SDL_mixer.h>

class Sound : public Trackable
{
public:
	Sound(std::string filename);
	~Sound();

	void fadeInSound(int fadeInMillis);
	void fadeOutSound(int fadeOutMillis);
	bool isPlaying();

private:
	Mix_Chunk* mSound = nullptr;
	int mChannel;
};

#endif
