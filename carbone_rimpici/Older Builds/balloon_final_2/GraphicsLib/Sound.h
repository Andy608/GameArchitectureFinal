#ifndef SOUND_H_
#define SOUND_H_

#include <Trackable.h>
#include <SDL.h>
#include <SDL_mixer.h>

class Sound : public Trackable
{
public:
	Sound(std::string filename, bool isSoundEffect);
	~Sound();

	void fadeInSound(int fadeInMillis);
	void fadeOutSound(int fadeOutMillis);
	bool isPlaying();

private:
	Mix_Chunk* mSound = nullptr;
	Mix_Music* mMusic = nullptr;
	int mChannel;
	bool mIsSoundEffect;
};

#endif
