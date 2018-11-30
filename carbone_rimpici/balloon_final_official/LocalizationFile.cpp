/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

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