/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef EVENT_SYSTEM_H_
#define EVENT_SYSTEM_H_

#include <map>
#include <Trackable.h>
#include "Event.h"

class EventListener;

class EventSystem : public Trackable
{
public:
	static EventSystem* getInstance();
	static void initInstance();
	static void cleanupInstance();

	//Disable any form of copying for a EventSystem object.
	EventSystem(const EventSystem& copy) = delete;
	void operator=(const EventSystem& copy) = delete;

	static void fireEvent(const Event& theEvent);
	static void addListener(Event::EnumEventType type, EventListener* pListener);
	static void removeListener(Event::EnumEventType type, EventListener* pListener);
	static void removeListenerFromAllEvents(EventListener* pListener);

private:
	static EventSystem* smpInstance;

	std::multimap<Event::EnumEventType, EventListener*> mListenerMap;

	inline EventSystem() {};
	inline ~EventSystem() {};

	void dispatchAllEvents(const Event& theEvent);
};

#endif