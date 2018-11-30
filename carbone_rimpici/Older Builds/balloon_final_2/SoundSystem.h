/*#ifndef SOUND_SYSTEM_H_
#define SOUND_SYSTEM_H_

#include <Trackable.h>
#include <vector>
#include <Sound.h>

class SoundSystem : public Trackable
{
public:
	SoundSystem();
	~SoundSystem();

	void init();
	void cleanup();

	Sound* getSound() { return balloonSound; };

private:
	std::vector<Sound*> mSoundList;
	Sound* balloonSound;
};

#endif
*/