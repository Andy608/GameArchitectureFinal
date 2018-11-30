#include "RectBounds.h"
#include <string>
#include <iostream>

RectBounds::RectBounds(int startingX, int startingY, int width, int height) :
	mStartingX(startingX),
	mStartingY(startingY),
	mWidth(width),
	mHeight(height)
{

}

RectBounds::~RectBounds()
{

}

bool RectBounds::isPointInBounds(Vector2D point)
{
	return isPointInBounds((int)point.getX(), (int)point.getY());
}

bool RectBounds::isPointInBounds(int x, int y)
{
	if (x > mStartingX && y > mStartingY && x < (mStartingX + mWidth) && y < (mStartingY + mHeight))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool RectBounds::isBoundsLeftOfHorizontalLine(float xCoordinate)
{
	bool isPastLine = false;

	if ((mStartingX + mWidth) < xCoordinate)
	{
		isPastLine = true;
	}

	return isPastLine;
}

bool RectBounds::isIntersecting(RectBounds* otherBounds)
{
	bool isIntersecting = false;

	if ((mStartingX < (otherBounds->mStartingX + otherBounds->mWidth)) &&
		((mStartingX + mWidth) > otherBounds->mStartingX) &&
		(mStartingY < (otherBounds->mStartingY + otherBounds->mHeight)) &&
		((mHeight + mStartingY) > otherBounds->mStartingY))
	{
		isIntersecting = true;
	}

	return isIntersecting;
}