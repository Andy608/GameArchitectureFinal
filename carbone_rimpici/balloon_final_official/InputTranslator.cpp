/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "InputTranslator.h"
#include <EventSystem.h>
#include <Event.h>
#include "GameEvent.h"
#include <System.h>
#include <InputSystem.h>

InputTranslator::InputTranslator() : 
	EventListener(EventSystem::getInstance())
{

}

InputTranslator::~InputTranslator()
{
	cleanup();
}

bool InputTranslator::init()
{
	if (!mIsInitialized)
	{
		mIsInitialized = true;

		EventSystem::addListener(Event::EnumEventType::_INPUT_EVENT, this);
		EventSystem::addListener(Event::EnumEventType::_MOUSE_EVENT, this);

		//Add new key pairs here - get keys from file eventually
		mInputMap.insert(std::make_pair(EnumKeyInput::SPACE_KEY, static_cast<Event::EnumEventType>(GameEvent::EnumGameEventType::_BURN_FUEL_EVENT)));
		mInputMap.insert(std::make_pair(EnumKeyInput::ESCAPE_KEY, Event::EnumEventType::_QUIT_EVENT));
	}

	return mIsInitialized;
}

void InputTranslator::cleanup()
{
	if (mIsInitialized)
	{
		EventSystem::removeListener(Event::EnumEventType::_INPUT_EVENT, this);
		EventSystem::removeListener(Event::EnumEventType::_MOUSE_EVENT, this);
		EventSystem::removeListener(Event::EnumEventType::_QUIT_EVENT, this);
	}
}

Event::EnumEventType InputTranslator::getEventFromMapping(int originalMapping)
{
	Event::EnumEventType eventValue = Event::EnumEventType::_INVALID_EVENT_TYPE;

	std::map<int, Event::EnumEventType>::iterator iter = mInputMap.find(originalMapping);

	if (iter != mInputMap.end())
	{
		eventValue = iter->second;
	}

	return eventValue;
}

void InputTranslator::handleEvent(const Event& theEvent)
{
	switch (theEvent.getType())
	{
	case Event::EnumEventType::_INPUT_EVENT:
		const KeyboardEvent& inputEvent = static_cast<const KeyboardEvent&>(theEvent);
		Event::EnumEventType translatedEventType = getEventFromMapping(inputEvent.getInputCode());

		bool isKeyDown = inputEvent.isKeyDown();

		if (translatedEventType == GameEvent::EnumGameEventType::_BURN_FUEL_EVENT)
		{
			fireTranslatedEvent(BurnFuelEvent(isKeyDown));
		}

		if (isKeyDown)
		{
			switch (translatedEventType)
			{
			case Event::EnumEventType::_QUIT_EVENT:
				fireTranslatedEvent(WindowClosedEvent());
				break;
			}
		}
		else
		{
			switch (translatedEventType)
			{
			case GameEvent::EnumGameEventType::_BURN_FUEL_EVENT:
				fireTranslatedEvent(BurnFuelEvent(isKeyDown));
				break;
			}
		}
	}
}

void InputTranslator::fireTranslatedEvent(const Event& theEvent)
{
	EventSystem::fireEvent(theEvent);
}