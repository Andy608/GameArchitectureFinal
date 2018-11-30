/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef SAVE_MANAGER_H_
#define SAVE_MANAGER_H_

#include <Trackable.h>
#include <map>
#include <string>
#include <Vector2D.h>
#include "SaveFile.h"
#include "AssetContainer.h"

class SaveManager : public Trackable
{
public:
	SaveManager();
	~SaveManager();

	void addSaveFile(std::string key, std::string fileSrc);

	void saveAllData();
	void deleteAllSaveData();

	SaveFile* getSaveFile(std::string key) const;

private:
	bool mIsLoaded;

	std::map<std::string, SaveFile*> mSaveFiles;
};

#endif