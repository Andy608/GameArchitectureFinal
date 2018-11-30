/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "EventListener.h"
#include "EventSystem.h"

EventListener::EventListener(EventSystem* pEventSystem) :
	mpEventSystem(pEventSystem)
{

}

EventListener::~EventListener()
{
	mpEventSystem->removeListenerFromAllEvents(this);
}
