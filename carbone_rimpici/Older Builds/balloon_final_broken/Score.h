#ifndef SCORE_H_
#define SCORE_H_

#include "Vector2D.h"
#include <Trackable.h>
#include "SettingsFile.h"

class Font;
struct Color;

class Score : public Trackable
{
public:
	Score(Font* font, Color* color, double timingForUpdate, int scoreDifficultyChange, Vector2D scoreLoc);
	~Score();

	void update(float deltaTime);
	void draw();
	void save();
	void load(SettingsFile& saveDataFile);

	int getDifficultyTracking() { return mScoreDifficultyTracking; };
	int getScoreDifficultyChange() { return mScoreDifficultyChange; };

	void resetScoreDifficultyTracking() { mScoreDifficultyTracking = 0; };

private:
	int mCurrentScore;
	int mScoreDifficultyTracking;		//keeps track of the current progress towards the mSDChange number
	int mScoreDifficultyChange;			//is what the Tracking has to be at for the speed to change
	Font* mScoreFont;
	Color* mScoreColor;

	double mStoredTime;
	double mUpdateTime;
	Vector2D mScoreTextLocation;
};

#endif