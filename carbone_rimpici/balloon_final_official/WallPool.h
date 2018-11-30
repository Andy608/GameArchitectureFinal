/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef WALL_POOL_H_
#define WALL_POOL_H_

#include <Trackable.h>
#include <Vector2D.h>
#include "Wall.h"

class WallPool : public Trackable
{
public:
	WallPool(int poolSize);
	~WallPool();

	Wall* createWall(float x, float y, float horizontalAcceleration, float horizontalVelocity);

	void update(float deltaTime);
	void draw();

	bool checkCollision(RectBounds* bounds);

private:
	const int mPOOL_SIZE;
	Wall* mpWalls;

	Wall* mpFirstAvailableWall;
};

#endif