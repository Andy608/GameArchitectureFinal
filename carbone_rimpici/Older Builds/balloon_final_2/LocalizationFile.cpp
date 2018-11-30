#include "LocalizationFile.h"

std::string LocalizationFile::smLanguageStrings[] = { "english", "french", "spanish" };

LocalizationFile::LocalizationFile(EnumLanguage language, std::string fileSrc) :
	SettingsFile(fileSrc),
	mLanguage(language)
{

}

LocalizationFile::~LocalizationFile()
{

}