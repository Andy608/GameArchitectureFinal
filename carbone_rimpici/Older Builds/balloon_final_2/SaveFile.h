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