/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef RECT_BOUNDS_H_
#define RECT_BOUNDS_H_

#include <Trackable.h>
#include <Vector2D.h>

class RectBounds : public Trackable
{
public:
	RectBounds(int startingX, int startingY, int width, int height);
	~RectBounds();

	bool isPointInBounds(Vector2D point);
	bool isPointInBounds(int x, int y);

	bool isBoundsLeftOfHorizontalLine(float xCoordinate);
	bool isIntersecting(RectBounds* otherBounds);
	
	inline void reverseY() { mStartingY = -mStartingY; };

	inline void updateBounds(int startingX, int startingY, int width, int height)
	{
		mStartingX = startingX;
		mStartingY = startingY;
		mWidth = width;
		mHeight = height;
	};

public:
	int mStartingX;
	int mStartingY;
	int mWidth;
	int mHeight;
};

#endif