/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef INPUT_SYSTEM_H_
#define INPUT_SYSTEM_H_

#include <Trackable.h>
#include <SDL.h>
#include <SDL_keycode.h>
#include <Vector2D.h>

enum EnumMouseInput
{
	//Mouse Input
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	MIDDLE_CLICK = 4,
};

enum EnumKeyInput
{
	//Keyboard Input
	ESCAPE_KEY = SDLK_ESCAPE,
	ENTER_KEY = SDLK_RETURN,
	SPACE_KEY = SDLK_SPACE,
	S_KEY = SDLK_s,
	F_KEY = SDLK_f,
	L_KEY = SDLK_l,

	UP_KEY = SDLK_UP,
	DOWN_KEY = SDLK_DOWN,
	LEFT_KEY = SDLK_LEFT,
	RIGHT_KEY = SDLK_RIGHT
};

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	bool init();
	void cleanup();

	void update(float deltaTime);

	SDL_Event getEventQueue() const;
	Vector2D getMousePosition() const;

private:
	//Keeps track of the input from allegro. Send updates about input to the event listener
	bool mIsInitialized;
	bool mIsMouseDown = false;
	bool mIsNewMousePress = false;
	SDL_Event mpEventQueue;
};

#endif