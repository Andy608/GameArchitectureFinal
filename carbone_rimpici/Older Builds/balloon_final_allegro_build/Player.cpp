#include "Player.h"
#include <EventSystem.h>
#include <GraphicsSystem.h>

Player::Player(const Sprite& pIdleSprite) :
	AnimatedObject(pIdleSprite),
	EventListener(EventSystem::getInstance()),
	mIsBurningFuel(false)
{
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_BURN_FUEL_EVENT), this);

	mpTransform->setAcceleration("gravity", Vector2D(0.0f, -9.81f));
	mpTransform->setScaleFactor(80.0);
	mpTransform->setMaxSpeed(400.0f);
	mpTransform->setPosition(Vector2D(300, -50));
}

Player::~Player()
{

}

void Player::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	//Go up! and maybe take fuel away	
	case GameEvent::EnumGameEventType::_BURN_FUEL_EVENT:
		handleBurnFuelEvent(static_cast<const BurnFuelEvent&>(theEvent));
		break;
	}
}

void Player::update(float deltaTime)
{
	GameObject::update(deltaTime);
}

void Player::draw()
{
	//Coordinates are reversed in SDL: EX 0,0 is top left not bottom left.
	GraphicsSystem::draw(static_cast<int>(mpTransform->getPosition().getX()), static_cast<int>(-mpTransform->getPosition().getY()), mpIdleSprite);
}

void Player::handleBurnFuelEvent(const BurnFuelEvent& theEvent)
{
	mIsBurningFuel = theEvent.shouldBurnFuel();

	if (mIsBurningFuel)
	{
		mpTransform->setAcceleration("lift", Vector2D(0.0f, 18.0f));
	}
	else
	{
		mpTransform->removeAcceleration("lift");
	}
}