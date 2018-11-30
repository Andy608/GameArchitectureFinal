#include "RectBounds.h"

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