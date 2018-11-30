/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "Transform.h"
#include <string>

const int Transform::UNLIMITED_SPEED = -1;

Transform::Transform(Vector2D position, Vector2D velocity, Vector2D acceleration, float maxSpeed, float scaleFactor) :
	mPosition(position),
	mVelocity(velocity),
	mAcceleration(acceleration),
	mMaxSpeed(maxSpeed),
	mScaleFactor(scaleFactor)
{

}

Transform::~Transform()
{

}

void Transform::update(float deltaTime)
{
	//Convert from milliseconds to seconds for physics
	deltaTime /= 1000.0f;

	//Change Position
	mPosition += (mVelocity * deltaTime);
	
	//Change Velocity
	mVelocity += (mAcceleration * deltaTime);

	updateAcceleration();

	//Debug
	//std::cout << "Delta: " << std::to_string(deltaTime) << " Acceleration: " << std::to_string(mAcceleration.getY()) << " Velocity: " << std::to_string(mVelocity.getY()) << " Position: " << std::to_string(mPosition.getY()) << std::endl;
}

void Transform::addAcceleration(std::string accelerationName, Vector2D addedAcceleration)
{
	auto accelerationPair = mAccelerationForceList.find(accelerationName);
	
	//If there is already an acceleration in the list, add the accelerations together.
	if (accelerationPair != mAccelerationForceList.end())
	{
		accelerationPair->second += addedAcceleration;
	}
	//If it isn't in the list, create a new spot for it.
	else
	{
		mAccelerationForceList.insert(std::make_pair(accelerationName, addedAcceleration));
	}
}

void Transform::removeAcceleration(std::string accelerationName)
{
	auto accelerationPair = mAccelerationForceList.find(accelerationName);

	//If there is already an acceleration in the list, add the accelerations together.
	if (accelerationPair != mAccelerationForceList.end())
	{
		mAccelerationForceList.erase(accelerationName);
	}
}

//Use the set acceleration to set the acceleration to a certain value so the velocity will increase by that acceleration.
void Transform::setAcceleration(std::string accelerationName, Vector2D newAcceleration)
{
	auto accelerationPair = mAccelerationForceList.find(accelerationName);

	//If there is already an acceleration in the list, set the acceleration to the new one.
	if (accelerationPair != mAccelerationForceList.end())
	{
		accelerationPair->second = newAcceleration;
	}
	//If it isn't in the list, create a new spot for it.
	else
	{
		mAccelerationForceList.insert(std::make_pair(accelerationName, newAcceleration));
	}
}

void Transform::setAcceleration(std::string accelerationName, float x, float y)
{
	auto accelerationPair = mAccelerationForceList.find(accelerationName);

	//If there is already an acceleration in the list, set the acceleration to the new one.
	if (accelerationPair != mAccelerationForceList.end())
	{
		accelerationPair->second.setX(x);
		accelerationPair->second.setY(y);
	}
	//If it isn't in the list, create a new spot for it.
	else
	{
		mAccelerationForceList.insert(std::make_pair(accelerationName, Vector2D(x, y)));
	}

	updateAcceleration();
}

void Transform::updateAcceleration()
{
	Vector2D acceleration;
	auto iter = mAccelerationForceList.begin();
	for (; iter != mAccelerationForceList.end(); ++iter)
	{
		acceleration += iter->second;
	}

	mAcceleration = acceleration * mScaleFactor;

	if (mMaxSpeed != UNLIMITED_SPEED && mVelocity.getLengthSquared() > (mMaxSpeed * mMaxSpeed))
	{
		mVelocity.normalize();
		mVelocity *= mMaxSpeed;
		mAcceleration.normalize();
	}
}