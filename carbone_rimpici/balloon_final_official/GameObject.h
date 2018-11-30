/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <Trackable.h>
#include "Transform.h"
#include "Sprite.h"
#include "RectBounds.h"

class GameObject : public Trackable
{
public:
	GameObject(const Sprite& pIdleSprite);
	virtual ~GameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;

	inline const Transform& getTransform() const { return *mpTransform; };
	inline RectBounds* getRectBounds() const { return mpBounds; };
	inline const Sprite& getIdleSprite() const { return mIdleSprite; };

protected:
	const Sprite& mIdleSprite;
	Transform* mpTransform;
	RectBounds* mpBounds;
};

#endif