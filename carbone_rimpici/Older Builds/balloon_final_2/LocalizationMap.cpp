#include "LocalizationMap.h"
#include <EventSystem.h>
#include "GameEvent.h"
#include "SaveManager.h"
#include "Game.h"

LocalizationMap::LocalizationMap() :
	mIsInitialized(false)
{

}

LocalizationMap::~LocalizationMap()
{
	cleanup();
}

bool LocalizationMap::initLangauges(SettingsFile& languagesFile)
{
	if (!mIsInitialized)
	{
		addLanguage("english", new LocalizationFile(EnumLanguage::ENGLISH, languagesFile.getSettingFromKey("english")));
		addLanguage("french", new LocalizationFile(EnumLanguage::FRENCH, languagesFile.getSettingFromKey("french")));
		addLanguage("spanish", new LocalizationFile(EnumLanguage::SPANISH, languagesFile.getSettingFromKey("spanish")));
		//addLanguage(new LocalizationFile(EnumLanguage::SPANISH, languagesFile.getSettingFromKey("spanish")));
		//addLanguage(new LocalizationFile(EnumLanguage::PIRATE, languagesFile.getSettingFromKey("pirate")));

		mIsInitialized = true;

		try
		{
			SaveFile* saveDataFile = Game::getInstance()->getSaveManager()->getSaveFile("options_save_data");
			Game::getInstance()->getLocalizationMap()->setCurrentLanguage(saveDataFile->getSettingFromKey("language"));
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
			mIsInitialized = false;
		}
	}

	return mIsInitialized;
}

void LocalizationMap::cleanup()
{
	if (mIsInitialized)
	{
		mLocalizationFiles.clearAssets();
		mIsInitialized = false;
	}
}

void LocalizationMap::addLanguage(std::string key, LocalizationFile* supportedLanguage)
{
	mLocalizationFiles.addAsset(supportedLanguage->getLanguage(), supportedLanguage);
	mLanguageList.insert(std::make_pair(key, supportedLanguage->getLanguage()));
}

void LocalizationMap::setCurrentLanguage(EnumLanguage languageType)
{
	LocalizationFile* foundLanguage = mLocalizationFiles.getAsset(languageType);

	if (foundLanguage == nullptr)
	{
		throw std::exception("Language is invalid! Have you added the language to the LocalizationMap yet?");
	}
	else
	{
		mCurrentLanguage = foundLanguage;
		EventSystem::getInstance()->fireEvent(LanguageChangedEvent());
	}
}

std::string LocalizationMap::getLocalizedString(std::string keyID)
{
	try
	{
		return mCurrentLanguage->getSettingFromKey(keyID);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return "INVALID_LOCALIZED_STRING :o";
	}
}

void LocalizationMap::setCurrentLanguage(std::string languageName)
{
	auto languageIter = mLanguageList.find(languageName);

	if (languageIter == mLanguageList.end())
	{
		setCurrentLanguage(EnumLanguage::ENGLISH);
	}
	else
	{
		setCurrentLanguage(languageIter->second);
	}
}