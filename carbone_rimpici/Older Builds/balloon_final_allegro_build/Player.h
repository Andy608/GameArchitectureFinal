#ifndef PLAYER_H_
#define PLAYER_H_

#include "AnimatedObject.h"
#include "EventListener.h"
#include "GameEvent.h"

class Player : public AnimatedObject, EventListener
{
public:
	Player(const Sprite& pIdleSprite);
	virtual ~Player();

	virtual void handleEvent(const Event& theEvent);
	virtual void update(float deltaTime);
	virtual void draw();

private:
	bool mIsBurningFuel;

	void handleBurnFuelEvent(const BurnFuelEvent& theEvent);
};

#endif