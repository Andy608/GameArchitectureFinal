#include "Player.h"
#include <EventSystem.h>
#include <GraphicsSystem.h>
#include "Game.h"
#include "SaveManager.h"
#include "AssetManager.h"

Player::Player(const Sprite& pIdleSprite) :
	AnimatedObject(pIdleSprite),
	EventListener(EventSystem::getInstance()),
	mIsBurningFuel(false)
{
	EventSystem::addListener(static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_BURN_FUEL_EVENT), this);

	mpTransform->setAcceleration("gravity", Vector2D(0.0f, -9.81f));
	mpTransform->setScaleFactor(80.0);
	mpTransform->setMaxSpeed(400.0f);
	mpTransform->setPosition(Vector2D(300, -300));
}

Player::~Player()
{

}

void Player::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	//Go up! and maybe take fuel away in the future
	case GameEvent::EnumGameEventType::_BURN_FUEL_EVENT:
	{
		handleBurnFuelEvent(static_cast<const BurnFuelEvent&>(theEvent));
	}
		break;
	}
}

void Player::update(float deltaTime)
{
	GameObject::update(deltaTime);

	//std::cout << std::to_string(static_cast<int>(std::round(mpTransform->getPosition().getY())));

	float offsetX = mIdleSprite.getWidth() / 4.0f;
	float offsetY = mIdleSprite.getHeight() / 4.0f;

	mpBounds->updateBounds(static_cast<int>(std::round(mpTransform->getPosition().getX() + offsetX)),
		-static_cast<int>(std::round(mpTransform->getPosition().getY() - offsetY)),//when this is neg the bottom works, pos the top works...
		static_cast<int>(mIdleSprite.getWidth() / 2.0f), static_cast<int>(mIdleSprite.getHeight() / 2.0f));
}

void Player::draw()
{
	//Coordinates are reversed in SDL: EX 0,0 is top left not bottom left. That is why we do -y position.
	GraphicsSystem::draw(mpTransform->getPosition().getX(), -mpTransform->getPosition().getY(), mIdleSprite);
	//GraphicsSystem::drawRect(mpBounds->mStartingX, mpBounds->mStartingY, mpBounds->mWidth, mpBounds->mHeight, Color(1.0, 0.0, 0.0, 1.0));
	//std::cout << "X Pos: " << std::to_string(mpTransform->getPosition().getX()) << std::endl;
	//std::cout << "Y Pos: " << std::to_string(mpTransform->getPosition().getY()) << std::endl;
}

void Player::save()
{
	SaveManager* sm = Game::getInstance()->getSaveManager();
	sm->getSaveFile("game_save_data")->addSaveData("player_location_x", std::to_string(mpTransform->getPosition().getX()));
	sm->getSaveFile("game_save_data")->addSaveData("player_location_y", std::to_string(mpTransform->getPosition().getY()));
}

void Player::load(SettingsFile& saveDataFile)
{
	//mpTransform->setPosition(Vector2D(mpTransform->getPosition().getX(),
	//	std::stof(Game::getInstance()->getSaveManager()->getSettingsFile()->getSettingFromKey("player_location_y"))));

	mpTransform->setPosition(Vector2D(mpTransform->getPosition().getX(),
		std::stof(saveDataFile.getSettingFromKey("player_location_y"))));
}

void Player::handleBurnFuelEvent(const BurnFuelEvent& theEvent)
{
	mIsBurningFuel = theEvent.shouldBurnFuel();

	Sound* balloonSound = Game::getInstance()->getAssetManager()->getSound("balloon_sound");

	if (mIsBurningFuel)
	{
		mpTransform->setAcceleration("lift", Vector2D(0.0f, 18.0f));

		if (Game::getInstance()->isSoundOn() && !balloonSound->isPlaying())
			balloonSound->fadeInSound(500);
	}
	else
	{
		mpTransform->removeAcceleration("lift");

		if (Game::getInstance()->isSoundOn())
			balloonSound->fadeOutSound(500);
	}
}
