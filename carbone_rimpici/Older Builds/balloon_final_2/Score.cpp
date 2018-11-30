#include "Score.h"
#include <Font.h>
#include <Color.h>
#include <GraphicsSystem.h>
#include "Game.h"
#include "SaveManager.h"
#include "LocalizationMap.h"

#include <sstream>

Score::Score(Font* font, Color* color, double timingForUpdate, int scoreDifficultyChange, Vector2D scoreLoc)
{
	mCurrentScore = 0;
	mScoreDifficultyTracking = 0;
	mScoreDifficultyChange = scoreDifficultyChange;
	mScoreFont = font;
	mScoreColor = color;
	mStoredTime = timingForUpdate;
	mUpdateTime = timingForUpdate;
 	mScoreTextLocation = scoreLoc;
}

Score::~Score()
{

}

void Score::update(float deltaTime)
{
	deltaTime /= 1000.0f;

	mStoredTime -= (double) deltaTime;

	if (mStoredTime <= 0)
	{
		mStoredTime = mUpdateTime;

		mCurrentScore += 1;
		mScoreDifficultyTracking += 1;
	}
}

void Score::draw()
{
	GraphicsSystem::writeText(mScoreTextLocation.getX(), mScoreTextLocation.getY(), *mScoreFont, *mScoreColor, 
		Game::getInstance()->getLocalizationMap()->getLocalizedString("game_scene_score") + ": " + std::to_string(mCurrentScore));
}

void Score::save()
{
	SaveManager* sm = Game::getInstance()->getSaveManager();
	sm->getSaveFile("game_save_data")->addSaveData("score", std::to_string(mCurrentScore));
}

void Score::load(SettingsFile& saveDataFile)
{
	mCurrentScore = std::stoi(saveDataFile.getSettingFromKey("score"));
}