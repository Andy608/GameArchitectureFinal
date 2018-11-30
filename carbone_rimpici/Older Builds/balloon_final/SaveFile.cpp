#include "SaveFile.h"
#include <fstream>

SaveFile::SaveFile(std::string fileSrc) : SettingsFile(fileSrc)
{
	//std::ifstream readStream(fileSrc);

	//If the file is not already created, create a new one.
	/*if (!readStream.is_open())
	{
		std::ofstream fileStream;
		fileStream.open(fileSrc, std::ios::app);
		fileStream.close();
	}*/
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