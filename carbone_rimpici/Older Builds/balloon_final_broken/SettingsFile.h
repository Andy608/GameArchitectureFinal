/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef SETTINGS_FILE_H_
#define SETTINGS_FILE_H_

#include <Trackable.h>
#include <string>
#include <map>

class SettingsFile : public Trackable
{
public:
	SettingsFile(std::string fileSrc);
	virtual ~SettingsFile();

	std::string getSettingFromKey(std::string key);
	std::string getKeyFromSetting(std::string setting);

	void clearFile() const;

	bool isEmpty();

protected:
	std::map<std::string, std::string> mSettingsMap;
	std::string mFileSource;
};

#endif