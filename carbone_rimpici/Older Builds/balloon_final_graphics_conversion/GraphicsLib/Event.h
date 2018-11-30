/*
* Author:		Andrew Rimpici
* Date:			3/02/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Assignment 5
* Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#ifndef EVENT_H_
#define EVENT_H_

#include <Trackable.h>
#include <string>
#include <vector>
#include <Vector2D.h>

class Event : public Trackable
{
public:
	enum class EnumEventType : int
	{
		_INVALID_EVENT_TYPE = -1,
		_INPUT_EVENT,
		_MOUSE_EVENT,
		_QUIT_EVENT,
		_NUM_EVENT_TYPES
	};

	inline Event(EnumEventType type) :
		mType(type) {};

	inline virtual ~Event() {};

	inline EnumEventType getType() const { return mType; }

private:
	EnumEventType mType;
};

class KeyboardEvent : public Event
{
public:
	inline KeyboardEvent(int inputCode, bool isKeyDown) :
		mInputCode(inputCode),
		mIsKeyDown(isKeyDown),
		Event(EnumEventType::_INPUT_EVENT) {}

	inline virtual ~KeyboardEvent() {}

	inline const int& getInputCode() const { return mInputCode; };
	inline const bool& isKeyDown() const { return mIsKeyDown; };

private:
	int mInputCode;
	bool mIsKeyDown;
};

class MouseEvent : public Event
{
public:
	inline MouseEvent(int inputCode, bool isButtonDown, int xPosition, int yPosition) :
		mInputCode(inputCode),
		mIsMouseDown(isButtonDown),
		mMousePosition(Vector2D(xPosition, yPosition)),
		Event(EnumEventType::_MOUSE_EVENT) {};

	inline virtual ~MouseEvent() {};

	inline const int& getInputCode() const { return mInputCode; };
	inline const bool& isMouseDown() const { return mIsMouseDown; };
	inline const Vector2D& getMousePosition() const { return mMousePosition; };

private:
	int mInputCode;
	bool mIsMouseDown;
	Vector2D mMousePosition;
};

class WindowClosedEvent : public Event
{
public:
	inline WindowClosedEvent() :
		Event(EnumEventType::_QUIT_EVENT) {};

	inline virtual ~WindowClosedEvent() {};
};

#endif