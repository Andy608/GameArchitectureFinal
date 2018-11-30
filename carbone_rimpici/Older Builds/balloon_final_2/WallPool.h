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
	//void save();
	//void load(SettingsFile& saveDataFile, float acceleration, float velocity);

	bool checkCollision(RectBounds* bounds);

private:
	const int mPOOL_SIZE;
	Wall* mpWalls;

	Wall* mpFirstAvailableWall;
};

#endif