/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef SAVE_FILE_H_
#define SAVE_FILE_H_

#include "SettingsFile.h"

class SaveFile : public SettingsFile
{
public:
	SaveFile(std::string fileSrc);
	virtual ~SaveFile();

	void addSaveData(std::string key, std::string value);

	void saveDataToFile() const;
	void deleteSaveData();

};

#endif