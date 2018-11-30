#ifndef GAME_EVENT_H_
#define GAME_EVENT_H_

#include <Event.h>

class GameEvent : public Event
{
public:
	enum EnumGameEventType : int
	{
		//Hot air balloons use fire to trap gas and make the balloons go up
		_BURN_FUEL_EVENT = EnumEventType::_NUM_EVENT_TYPES + 1,
		_NUM_EVENT_TYPES
	};

	inline GameEvent(EnumGameEventType type)
	try : Event(static_cast<EnumEventType>(type))
	{

	}
	catch (...)
	{
		std::cout << "No event with type id: \'" << std::to_string(type) << "\'." << std::endl;
	}
};

class BurnFuelEvent : public GameEvent
{
public:
	inline BurnFuelEvent(bool shouldBurnFuel) :
		GameEvent(GameEvent::EnumGameEventType::_BURN_FUEL_EVENT),
		mShouldBurnFuel(shouldBurnFuel)
		{};

	inline bool shouldBurnFuel() const { return mShouldBurnFuel; };

private:
	bool mShouldBurnFuel;
};

#endif