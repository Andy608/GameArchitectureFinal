/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "SettingsFile.h"
#include <fstream>
#include <iostream>

SettingsFile::SettingsFile(std::string fileSrc)
{
	std::ifstream readStream;
	readStream.open(fileSrc, std::ifstream::in);

	if (readStream.is_open())
	{
		std::string line;
		unsigned int i;

		while (std::getline(readStream, line))
		{
			if (line.empty() || line.at(0) == '*')
			{
				continue;
			}

			for (i = 0; i < line.size(); ++i)
			{
				if (line.at(i) == '=')
				{
					mSettingsMap.insert(std::make_pair(line.substr(0, i), line.substr(i + 1)));
					std::cout << "Inserting Key: " << line.substr(0, i) << ", Value: " << line.substr(i + 1) << std::endl;
					break;
				}
			}
		}
	}
	else
	{
		std::cout << "Unable to read file: \'" << fileSrc << "\'";
	}

	readStream.close();
}

SettingsFile::~SettingsFile()
{

}

std::string SettingsFile::getSettingFromKey(std::string key)
{
	std::string value = "";
	std::map<std::string, std::string>::iterator iter = mSettingsMap.find(key);

	if (iter != mSettingsMap.end())
	{
		value = iter->second;
	}
	else
	{
		throw std::exception(("Could not find setting with key: \'" + key + "\'").c_str());
	}

	return value;
}

std::string SettingsFile::getKeyFromSetting(std::string setting)
{
	std::string key = "";
	std::map<std::string, std::string>::iterator iter;

	for (iter = mSettingsMap.begin(); iter != mSettingsMap.end(); ++iter)
	{
		if (iter->second == setting)
		{
			key = iter->first;
		}
	}

	return key;
}