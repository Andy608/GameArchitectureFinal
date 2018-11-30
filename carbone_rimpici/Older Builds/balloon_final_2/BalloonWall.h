#ifndef BALLOON_WALL_H_
#define BALLOON_WALL_H_

#include "Wall.h"

class BalloonWall : public Wall
{
public:
	static int getRandomBalloonIndex(unsigned int rows, unsigned int columns);

	BalloonWall(const SpriteSheet& sprite, int spriteSheetIndex, int minHeight, int maxHeight, int startingSpeed);
	~BalloonWall();

	void update(float deltaTime);
	void draw();
	inline void invertSpeed() { mSpeed = -mSpeed; };
	inline float getSpeed() const { return mSpeed; };
	inline float getCoolDown() const { return mTurnAroundCoolDown; };
	inline const void resetCoolDown() { mTurnAroundCoolDown = TURN_AROUND_COOLDOWN; };
	inline const int& getSpriteSheetIndex() const { return mSpriteSheetIndex; };

private:
	static const float TURN_AROUND_COOLDOWN;
	int mSpriteSheetIndex;
	int mMaxHeight;
	int mMinHeight;
	float mSpeed;
	float mTurnAroundCoolDown;

	bool mIsGoingUp;
};

#endif