/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "SaveManager.h"
#include <iostream>

SaveManager::SaveManager() :
	mSaveFiles(std::map<std::string, SaveFile*>()),
	mIsLoaded(false)
{

}

SaveManager::~SaveManager()
{
	for (auto iter : mSaveFiles)
	{
		if (iter.second)
		{
			delete iter.second;
		}
	}

	mSaveFiles.clear();
}

void SaveManager::addSaveFile(std::string key, std::string fileSrc)
{
	mSaveFiles.insert(std::make_pair(key, new SaveFile(fileSrc)));
}

void SaveManager::saveAllData()
{
	for (auto iter : mSaveFiles)
	{
		iter.second->clearFile();
		iter.second->saveDataToFile();
	}
}

void SaveManager::deleteAllSaveData()
{
	for (auto iter : mSaveFiles)
	{
		iter.second->deleteSaveData();
	}
}

SaveFile* SaveManager::getSaveFile(std::string key) const
{
	auto iter = mSaveFiles.find(key);

	if (iter == mSaveFiles.end())
	{
		throw("Could not find save file with key: \'" + key + "\'");
	}
	else
	{
		return iter->second;
	}
}