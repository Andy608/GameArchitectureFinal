#ifndef LOCALIZATION_FILE_H_
#define LOCALIZATION_FILE_H_

#include "SettingsFile.h"

enum EnumLanguage
{
	ENGLISH,
	FRENCH,
	SPANISH,
	//PIRATE,
	LANGUAGE_COUNT
};

class LocalizationFile : public SettingsFile
{
public:
	LocalizationFile(EnumLanguage language, std::string fileSrc);
	~LocalizationFile();

	inline EnumLanguage getLanguage() const { return mLanguage; };
	static inline std::string enumToString(EnumLanguage language) { return smLanguageStrings[(int)language]; };

private:
	static std::string smLanguageStrings[];
	EnumLanguage mLanguage;
};

#endif