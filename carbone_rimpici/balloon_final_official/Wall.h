/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef WALL_H_
#define WALL_H_

#include "GameObject.h"
#include <string>
#include "Game.h"
#include "AssetManager.h"

class Wall : public GameObject
{
public:
	friend class WallPool;
	friend class WallManager;

	inline Wall* getNext() const { return mState.pNext; };
	inline void setNext(Wall* next) { mState.pNext = next; };

	inline bool isInUse() const { return mIsInUse; };
	inline bool isOnScreen() const { return mIsOnScreen; };
	inline void setOnScreen(bool onScreen) { mIsOnScreen = onScreen; };

	void init(float x, float y, float horizontalAcceleration, float horizontalVelocity);

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	static const std::string ACCELERATION_ID;
	bool mIsOnScreen;
	bool mIsInUse;

	union
	{
		struct
		{
			int mHeightOffset;
		} mLiving;

		Wall* pNext;

	} mState;

	Wall(const Sprite& sprite = *Game::getInstance()->getAssetManager()->getSprite("wall_sprite"));
	virtual ~Wall();

	bool flewOffScreenToLeft();
};

#endif