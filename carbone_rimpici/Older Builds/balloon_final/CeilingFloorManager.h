#ifndef CEILING_FLOOR_MANAGER_H_
#define CEILING_FLOOR_MANAGER_H_

#include <Trackable.h>
#include "SettingsFile.h"
#include "CeilingFloorBlock.h"
#include <Sprite.h>
#include <vector>

class CeilingFloorManager : public Trackable
{
	friend class GameScene;
public:
	CeilingFloorManager(const Sprite& blockSprite, const Sprite& wallSprite, double blockVelocity, double velocityIncrement);
	~CeilingFloorManager();

	void update(float deltaTime);
	void draw();
	void save();
	void load(SettingsFile& saveDataFile);

	int getSpriteWidth() { return mCeilingFloorSprite.getWidth(); };
	int getSpriteHeight() { return mCeilingFloorSprite.getHeight(); };

	void cleanup();

	void increaseSpeed();

private:
	const Sprite& mCeilingFloorSprite;
	const Sprite& mFloatingWallSprite;
	Vector2D mVelocity;
	double mVelocityIncrement;

	int mNumOfBlocksBetweenWalls = 8;
	int mCurrentNumOfBlocksBetweenWalls = 8;
	void spawnFloatingWall();

	std::vector<CeilingFloorBlock*> mCeilingBlocks;
	std::vector<CeilingFloorBlock*> mFloorBlocks;
	std::vector<CeilingFloorBlock*> mFloatingWallBlocks;
};

#endif