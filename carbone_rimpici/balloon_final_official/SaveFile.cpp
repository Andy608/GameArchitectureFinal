/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "SaveFile.h"
#include <fstream>

SaveFile::SaveFile(std::string fileSrc) : SettingsFile(fileSrc)
{

}

SaveFile::~SaveFile()
{

}

void SaveFile::addSaveData(std::string key, std::string value)
{
	auto iter = mSettingsMap.find(key);
	if (iter != mSettingsMap.end())
	{
		iter->second = value;
	}
	else
	{
		mSettingsMap.insert(std::make_pair(key, value));
	}
}

void SaveFile::saveDataToFile() const
{
	std::ofstream oFile;

	oFile.open(mFileSource, std::ios::app);

	if (oFile.is_open())
	{
		for (auto& keyValue : mSettingsMap)
		{
			oFile << keyValue.first << "=" << keyValue.second << std::endl;
		}

		oFile.close();
	}
}

void SaveFile::deleteSaveData()
{
	clearFile();
	mSettingsMap.clear();
}