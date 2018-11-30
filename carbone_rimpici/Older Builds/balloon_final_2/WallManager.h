#ifndef WALL_MANAGER_H_
#define WALL_MANAGER_H_

#include <Trackable.h>
#include "WallPool.h"
#include "BalloonWall.h"
#include "HeightGenerator.h"
#include <vector>
#include "SettingsFile.h"

class WallManager : public Trackable
{
public:
	friend class GameScene;

	WallManager();
	~WallManager();

	void update(float deltaTime);
	void draw();
	void save();
	void load(SettingsFile& saveDataFile);

	inline void moveWalls(bool isMoving) { mIsMoving = isMoving; };
	inline bool isMoving() const { return mIsMoving; };

	bool isWallCollidingWith(RectBounds* bounds);
	bool isBalloonCollidingWith(RectBounds* bounds);

	void initNewGame();

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

	std::vector<BalloonWall*> mBalloonList;

	float mTimeTilBalloonSpawn;

	int getAmountOfWallsFitOnScreen();
	Wall* createWall(float x, float y, float acceleration, float velocity);

	void initWalls();
	void createBalloon();
	void createBalloon(float x, float y, int speed);
	void createBalloon(int spriteIndex, float x, float y, int speed);
	void deleteBalloon(unsigned int balloonIndex);
};

#endif