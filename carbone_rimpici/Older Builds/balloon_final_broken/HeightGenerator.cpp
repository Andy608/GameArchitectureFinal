#include "HeightGenerator.h"
#include <iostream>
#include <string>

const float HeightGenerator::PI = 3.14159265359;

HeightGenerator::HeightGenerator()
{
	reset();
}

HeightGenerator::~HeightGenerator()
{

}

float HeightGenerator::getNextHeight()
{
	mTimeCounter += degreeToRad(mFrequency * 1.0f);
	return getHeight(mTimeCounter);
}

float HeightGenerator::getHeight(float time)
{
	//Might need to change to radians
	return clamp(mMinHeightOffset, mMaxHeightOffset, mMagnitude * radToDegree(std::sinf(time)));
	//std::cout << std::to_string(mMagnitude * radToDegree(std::sinf(time))) << std::endl;
	//return radToDegree(mMagnitude * std::sinf(time));
}

float HeightGenerator::clamp(float min, float max, float value)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}

	return value;
}

float HeightGenerator::radToDegree(float rad)
{
	return rad / PI * 180.0f;
}

float HeightGenerator::degreeToRad(float rad)
{
	return rad / 180.0f * PI;
}