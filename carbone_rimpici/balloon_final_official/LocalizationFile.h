/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef LOCALIZATION_FILE_H_
#define LOCALIZATION_FILE_H_

#include "SettingsFile.h"

enum EnumLanguage
{
	ENGLISH,
	FRENCH,
	SPANISH,
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