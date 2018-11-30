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