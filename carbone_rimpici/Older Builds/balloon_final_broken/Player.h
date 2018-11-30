#ifndef PLAYER_H_
#define PLAYER_H_

#include "AnimatedObject.h"
#include "EventListener.h"
#include "GameEvent.h"
#include "SettingsFile.h"

class Player : public AnimatedObject, EventListener
{
public:
	Player(const Sprite& pIdleSprite);
	virtual ~Player();

	virtual void handleEvent(const Event& theEvent);
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void save();
	virtual void load(SettingsFile& saveDataFile);

private:
	bool mIsBurningFuel;

	void handleBurnFuelEvent(const BurnFuelEvent& theEvent);
};

#endif