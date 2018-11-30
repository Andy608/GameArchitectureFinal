/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <allegro5/allegro.h>
#include "InputSystem.h"
#include "System.h"
#include "Event.h"
#include "EventSystem.h"

InputSystem::InputSystem() :
	mIsInitialized(false)
{

}

InputSystem::~InputSystem()
{
	cleanup();
}


bool InputSystem::init()
{
	if (!mIsInitialized)
	{
		mIsInitialized = true;

		mpEventQueue = al_create_event_queue();

		if (!mpEventQueue)
		{
			std::cout << "Failed to create event queue." << std::endl;
			cleanup();
		}
		else if (!al_install_mouse())
		{
			std::cout << "Failed to install mouse input." << std::endl;
			cleanup();
		}
		else if (!al_install_keyboard())
		{
			std::cout << "Failed to install keyboard input." << std::endl;
			cleanup();
		}
		else
		{
			al_register_event_source(mpEventQueue, al_get_display_event_source(GraphicsSystem::getInstance()->mpDisplay));
			al_register_event_source(mpEventQueue, al_get_mouse_event_source());
			al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
		}
	}

	return mIsInitialized;
}

void InputSystem::cleanup()
{
	if (mIsInitialized)
	{
		al_uninstall_keyboard();
		al_uninstall_mouse();

		mIsInitialized = false;
	}
}

void InputSystem::update(float deltaTime)
{
	ALLEGRO_EVENT evnt;

	while (al_get_next_event(mpEventQueue, &evnt))
	{
		//Event from Allegro Event Queue
		switch (evnt.type)
		{
		case ALLEGRO_EVENT_KEY_DOWN:
			EventSystem::getInstance()->fireEvent(KeyboardEvent(evnt.keyboard.keycode, true));
			break;
		case ALLEGRO_EVENT_KEY_UP:
			EventSystem::getInstance()->fireEvent(KeyboardEvent(evnt.keyboard.keycode, false));
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			EventSystem::getInstance()->fireEvent(MouseEvent(evnt.mouse.button, true, evnt.mouse.x, evnt.mouse.y));
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			EventSystem::getInstance()->fireEvent(MouseEvent(evnt.mouse.button, false, evnt.mouse.x, evnt.mouse.y));
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			EventSystem::getInstance()->fireEvent(WindowClosedEvent());
			break;
		}
	}
}

ALLEGRO_EVENT_QUEUE* InputSystem::getEventQueue() const
{
	return mpEventQueue;
}

Vector2D InputSystem::getMousePosition() const
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	return Vector2D(mouseState.x, mouseState.y);
}