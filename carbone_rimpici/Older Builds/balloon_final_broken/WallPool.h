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

	Wall* createWall(bool isCeiling, float x, float y, float horizontalAcceleration, float horizontalVelocity);

	void update(float deltaTime);
	void draw();

	bool checkCollision(GameObject* pObject);

private:
	const int mPOOL_SIZE;
	Wall* mpWalls;

	Wall* mpFirstAvailableWall;
};

#endif