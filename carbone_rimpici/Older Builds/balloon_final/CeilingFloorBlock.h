#ifndef CEILING_FLOOR_BLOCK_H_
#define CEILING_FLOOR_BLOCK_H_

#include "AnimatedObject.h"
#include "SettingsFile.h"
#include <Vector2D.h>

class CeilingFloorBlock : public AnimatedObject
{
public:
	CeilingFloorBlock(const Sprite& idleSprite, Vector2D startingLocation, Vector2D startingVelocity);
	virtual ~CeilingFloorBlock();

	virtual void update(float deltaTime);
	virtual void draw();

	void setVelocity(Vector2D newVelocity) { mpTransform->setVelocity(newVelocity); };

	inline bool isOnScreen() { return mIsOnScreen; };
	inline void setOnScreen(bool onScreen) { mIsOnScreen = onScreen; };

private:
	bool mIsOnScreen;
};

#endif