/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <Trackable.h>
#include <Vector2D.h>
#include <map>
#include <string>

class Transform : public Trackable
{
public:
	//When max speed is set to -1 there is no max speed.
	Transform(Vector2D position = Vector2D(0, 0), Vector2D velocity = Vector2D(0, 0), Vector2D acceleration = Vector2D(0, 0), float maxSpeed = UNLIMITED_SPEED, float scaleFactor = 1.0f);
	~Transform();

	void update(float deltaTime);

	inline void reset()
	{
		mAcceleration.setX(0); mAcceleration.setY(0);
		mVelocity.setX(0); mVelocity.setY(0);
		mPosition.setX(0); mPosition.setY(0);
		//mOffset.setX(0); mOffset.setY(0);
		mMaxSpeed = static_cast<float>(UNLIMITED_SPEED);
		mScaleFactor = 1.0f;
		mAccelerationForceList.clear();
	};

	//Use add to make the transform ACCELERATION faster/slower over time.
	void addAcceleration(std::string accelerationName, Vector2D addedAcceleration);
	void removeAcceleration(std::string accelerationName);

	void setMaxSpeed(float speed) { mMaxSpeed = speed; };

	//Use the set acceleration to set the acceleration to a certain value so the velocity will increase by that acceleration.
	void setAcceleration(std::string accelerationName, Vector2D newAcceleration);
	void setAcceleration(std::string accelerationName, float x, float y);

	//Use this to set a starting velocity.
	inline void addVelocity(Vector2D addedVelocity) { mVelocity += addedVelocity; };
	inline void setVelocity(Vector2D newVelocity) { mVelocity = newVelocity; };
	inline void setVelocity(float x, float y) { mVelocity.setX(x); mVelocity.setY(y); };

	//Use this to set a starting position.
	inline void addPosition(Vector2D addedPosition) { mPosition += addedPosition; };
	inline void addPosition(float x, float y) { mPosition.setX(mPosition.getX() + x); mPosition.setY(mPosition.getY() + y); };

	inline void setPosition(Vector2D newPosition) { mPosition = newPosition; };
	inline void setPosition(float x, float y) { mPosition.setX(x); mPosition.setY(y); };

	inline const Vector2D& getAcceleration() const { return mAcceleration; };
	inline const Vector2D& getVelocity() const { return mVelocity; };
	inline const Vector2D& getPosition() const { return mPosition; };
	//inline Vector2D getOffsetPosition() const { return mPosition + mOffset; };

	//inline void setOffset(float x, float y) { mOffset.setX(x); mOffset.setY(y); };
	//inline const Vector2D& getOffset() const { return mOffset; };

	inline void setScaleFactor(float scale) { mScaleFactor = scale; };

private:
	const static int UNLIMITED_SPEED;
	float mMaxSpeed;
	float mScaleFactor;

	Vector2D mPosition;
	Vector2D mVelocity;
	Vector2D mAcceleration;
	//Vector2D mOffset;

	//<Acceleration Force Name, Acceleration Force>
	std::map<std::string, Vector2D> mAccelerationForceList;

	void updateAcceleration();
};

#endif