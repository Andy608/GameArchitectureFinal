/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef INPUT_TRANSLATOR_H_
#define INPUT_TRANSLATOR_H_

#include <EventListener.h>
#include <map>

class InputTranslator : public EventListener
{
public:
	InputTranslator();
	~InputTranslator();

	bool init();
	void cleanup();

	virtual void handleEvent(const Event& theEvent);

private:
	bool mIsInitialized;
	std::map<const int, Event::EnumEventType> mInputMap;
	
	Event::EnumEventType getEventFromMapping(int originalMapping);
	void fireTranslatedEvent(const Event& theEvent);
};

#endif