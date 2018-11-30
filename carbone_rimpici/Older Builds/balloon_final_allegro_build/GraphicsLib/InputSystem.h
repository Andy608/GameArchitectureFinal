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
#include <allegro5/keycodes.h>
#include <Vector2D.h>

struct ALLEGRO_EVENT_QUEUE;

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
	ESCAPE_KEY = ALLEGRO_KEY_ESCAPE,
	ENTER_KEY = ALLEGRO_KEY_ENTER,
	SPACE_KEY = ALLEGRO_KEY_SPACE,
	S_KEY = ALLEGRO_KEY_S,
	F_KEY = ALLEGRO_KEY_F,

	UP_KEY = ALLEGRO_KEY_UP,
	DOWN_KEY = ALLEGRO_KEY_DOWN,
	LEFT_KEY = ALLEGRO_KEY_LEFT,
	RIGHT_KEY = ALLEGRO_KEY_RIGHT
};

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	bool init();
	void cleanup();

	void update(float deltaTime);

	ALLEGRO_EVENT_QUEUE* getEventQueue() const;
	Vector2D getMousePosition() const;

private:
	//Keeps track of the input from allegro. Send updates about input to the event listener
	bool mIsInitialized;
	ALLEGRO_EVENT_QUEUE* mpEventQueue;
};

#endif