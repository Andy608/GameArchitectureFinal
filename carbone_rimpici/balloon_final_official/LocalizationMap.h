/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef LOCALIZATION_MAP_H_
#define LOCALIZATION_MAP_H_

#include <map>
#include <Trackable.h>
#include "LocalizationFile.h"
#include "AssetContainer.h"

class LocalizationMap : public Trackable
{
public:
	LocalizationMap();
	~LocalizationMap();

	bool initLangauges(SettingsFile& langaugesFile);
	void cleanup();

	void setCurrentLanguage(EnumLanguage languageType);
	void setCurrentLanguage(std::string languageName);

	std::string getLocalizedString(std::string keyID);

	inline EnumLanguage getLanguageType() const { if (mCurrentLanguage) { mCurrentLanguage->getLanguage(); return mCurrentLanguage->getLanguage(); } else { return EnumLanguage::ENGLISH; } };

private:
	bool mIsInitialized = false;

	LocalizationFile* mCurrentLanguage = nullptr;

	AssetContainer<EnumLanguage, LocalizationFile> mLocalizationFiles;
	std::map<std::string, EnumLanguage> mLanguageList;

	void addLanguage(std::string key, LocalizationFile* supportedLanguage);
};

#endif