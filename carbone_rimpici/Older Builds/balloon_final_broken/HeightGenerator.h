#ifndef HEIGHT_GENERATOR_H_
#define HEIGHT_GENERATOR_H_

#include <Trackable.h>

class HeightGenerator : public Trackable
{
public:
	static const float PI;
	
	HeightGenerator();
	~HeightGenerator();

	inline void setMinHeightOffset(float minHeightOffset) { mMinHeightOffset = minHeightOffset; };
	inline void setMaxHeightOffset(float maxHeightOffset) { mMaxHeightOffset = maxHeightOffset; };
	inline void setFrequency(float frequency) { mFrequency = frequency; };
	inline void setMagnitude(float magnitude) { mMagnitude = magnitude; };

	inline void reset()
	{
		mMinHeightOffset = 0;
		mMaxHeightOffset = 0;
		mFrequency = 1.0f;
		mMagnitude = 1.0f;
		mTimeCounter = 0.0f;
	}

	float HeightGenerator::getNextHeight();
	float getHeight(float time);

private:
	float mMinHeightOffset;
	float mMaxHeightOffset;

	float mFrequency;
	float mMagnitude;

	float mTimeCounter;

	float clamp(float min, float max, float value);
	float radToDegree(float rad);
	float degreeToRad(float rad);
};

#endif