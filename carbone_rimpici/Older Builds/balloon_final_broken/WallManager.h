#ifndef WALL_MANAGER_H_
#define WALL_MANAGER_H_

#include <Trackable.h>
#include "WallPool.h"
#include "HeightGenerator.h"
#include <vector>

class WallManager : public Trackable
{
public:
	friend class GameScene;

	WallManager();
	~WallManager();

	void update(float deltaTime);
	void draw();

	inline void moveWalls(bool isMoving) { mIsMoving = isMoving; };
	inline bool isMoving() const { return mIsMoving; };

	bool isWallCollidingWith(GameObject* pObject);

private:
	static const std::string ACCELERATION_ID;

	Vector2D mSpriteDimensions;
	WallPool* mpWallPool;
	bool mIsMoving;
	Transform* mpWallTransform;
	HeightGenerator* mpHeightGenerator;

	float mCeilingYBaseline;
	float mFloorYBaseline;

	std::vector<Wall*> mCeilingList;
	std::vector<Wall*> mFloorList;

	int getAmountOfWallsFitOnScreen();
	Wall* createWall(bool isCeiling, float x, float y, float acceleration, float velocity);

	void initWalls();
};

#endif