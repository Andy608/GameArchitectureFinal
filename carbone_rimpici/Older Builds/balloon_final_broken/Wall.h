#ifndef WALL_H_
#define WALL_H_

#include "GameObject.h"
#include <string>

class Wall : public GameObject
{
public:
	friend class WallPool;
	friend class WallManager;

	inline Wall* getNext() const { return mState.pNext; };
	inline void setNext(Wall* next) { mState.pNext = next; };

	inline bool isInUse() const { return mIsInUse; };
	inline bool isOnScreen() const { return mIsOnScreen; };

	void init(bool isCeiling, float x, float y, float horizontalAcceleration, float horizontalVelocity);

	virtual void update(float deltaTime);
	virtual void draw();

private:
	static const std::string ACCELERATION_ID;
	bool mIsOnScreen;
	bool mIsInUse;
	bool mIsCeiling;

	union
	{
		struct
		{
			int mHeightOffset;
		} mLiving;

		Wall* pNext;

	} mState;

	Wall();
	virtual ~Wall();

	bool flewOffScreenToLeft();
};

#endif