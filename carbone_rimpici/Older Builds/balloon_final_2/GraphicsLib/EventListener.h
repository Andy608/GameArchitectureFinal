/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef EVENT_LISTENER_H_
#define EVENT_LISTENER_H_

#include <Trackable.h>
#include "Event.h"

class EventSystem;

class EventListener : public Trackable
{
public:
	EventListener(EventSystem* pEventSystem);
	virtual ~EventListener();

	virtual void handleEvent(const Event& theEvent) = 0;

protected:
	EventSystem* getEventSystem() const { return mpEventSystem; };

private:
	EventSystem* mpEventSystem;
};

#endif