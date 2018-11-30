#ifndef HEIGHT_GENERATOR_H_
#define HEIGHT_GENERATOR_H_

#include <Trackable.h>

class HeightGenerator : public Trackable
{
public:
	static const double PI;

	//min inclusive, max exclusive
	static int getRandomInt(int lowerBound, int upperBound);
	
	HeightGenerator();
	~HeightGenerator();

	inline void setMinHeightOffset(float minHeightOffset) { mMinHeightOffset = minHeightOffset; };
	inline void setMaxHeightOffset(float maxHeightOffset) { mMaxHeightOffset = maxHeightOffset; };
	inline void setFrequency(float frequency) { mFrequency = frequency; };
	inline void setAmplitude(float amplitude) { mAmplitude = amplitude; };
	inline void setTime(float startTime) { mTimeCounter = startTime; };

	inline float getTime() const { return mTimeCounter; };
	inline float getFrequency() const { return mFrequency; };
	inline float getAmplitude() const { return mAmplitude; };

	inline void reset()
	{
		mMinHeightOffset = 0;
		mMaxHeightOffset = 0;
		mFrequency = 1.0f;
		mAmplitude = 1.0f;
		mTimeCounter = 0.0f;
	}

	float HeightGenerator::getNextHeight();
	float getHeight(float time);

private:
	float mMinHeightOffset;
	float mMaxHeightOffset;

	float mFrequency;
	float mAmplitude;

	float mTimeCounter;

	float clamp(float min, float max, float value);
	float radToDegree(float rad);
	float degreeToRad(float rad);
};

#endif