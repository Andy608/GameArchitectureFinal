/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "HeightGenerator.h"
#include <random>
#include <iostream>
#include <string>

const double HeightGenerator::PI = 3.14159265359;

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
	return clamp(mMinHeightOffset, mMaxHeightOffset, mAmplitude * radToDegree(std::sinf(time)));
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
	return rad / (float)(PI) * 180.0f;
}

float HeightGenerator::degreeToRad(float rad)
{
	return rad / 180.0f * (float)(PI);
}

int HeightGenerator::getRandomInt(int lowerBound, int upperBound)
{
	//Random unbiased created by "Walter" on https://stackoverflow.com/a/19728404
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
							   //std::uniform_int_distribution<int> uni((int)(mFloorBlocks[i].getBlockLoc().getY() - 30), (int)(mFloorBlocks[i].getBlockLoc().getY() + 30)); // guaranteed unbiased
	std::uniform_int_distribution<int> uni(lowerBound, upperBound); // guaranteed unbiased
	return uni(rng);
}