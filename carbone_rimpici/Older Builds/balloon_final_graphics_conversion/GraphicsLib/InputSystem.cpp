/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

//#include <allegro5/allegro.h>
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
	/*if (!mIsInitialized)
	{
		mIsInitialized = true;

		//mpEventQueue = al_create_event_queue();

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

	return mIsInitialized;*/
	return true;
}

void InputSystem::cleanup()
{
	/*if (mIsInitialized)
	{
		al_uninstall_keyboard();
		al_uninstall_mouse();

		mIsInitialized = false;
	}*/
}

void InputSystem::update(float deltaTime)
{
	//ALLEGRO_EVENT evnt;

	while (SDL_PollEvent(&mpEventQueue))
	{
		//Event from Allegro Event Queue
		switch (mpEventQueue.type)
		{
		case SDL_KEYDOWN:
			EventSystem::getInstance()->fireEvent(KeyboardEvent(mpEventQueue.key.keysym.sym, true));
			break;
		case SDL_KEYUP:
			EventSystem::getInstance()->fireEvent(KeyboardEvent(mpEventQueue.key.keysym.sym, false));
			break;
		case SDL_MOUSEBUTTONDOWN:
			EventSystem::getInstance()->fireEvent(MouseEvent(mpEventQueue.button.button, true, mpEventQueue.button.x, mpEventQueue.button.y));
			break;
		case SDL_MOUSEBUTTONUP:
			EventSystem::getInstance()->fireEvent(MouseEvent(mpEventQueue.button.button, false, mpEventQueue.button.x, mpEventQueue.button.y));
			break;
		case SDL_WINDOWEVENT_CLOSE:
			EventSystem::getInstance()->fireEvent(WindowClosedEvent());
			break;
		}
	}
}

SDL_Event InputSystem::getEventQueue() const
{
	return mpEventQueue;
}

Vector2D InputSystem::getMousePosition() const
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	return Vector2D(x, y);
}