/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef ASSET_MANAGER_H_
#define ASSET_MANAGER_H_

#include <Trackable.h>
#include <map>
#include <string>
#include <Vector2D.h>
#include "SettingsFile.h"
#include "AssetContainer.h"

#include <Sprite.h>
#include <SpriteSheet.h>
#include <GraphicsBuffer.h>
#include <Font.h>
#include <Color.h>
#include <Sound.h>

class AssetManager : public Trackable
{
public:
	AssetManager(SettingsFile& mainSettingsFile);
	inline ~AssetManager() {};

	bool loadAssets();

	GraphicsBuffer* getBuffer(std::string key) const;
	Sprite* getSprite(std::string key) const;
	SpriteSheet* getSpriteSheet(std::string key) const;
	float* getValue(std::string key) const;
	Color* getColor(std::string key) const;
	Sound* getSound(std::string key) const;
	Font* getFont(std::string key) const;
	Vector2D* getVector2D(std::string key) const;

private:
	bool mIsLoaded;

	SettingsFile& mMainSettingsFile;

	//Going to hold lists of...
	
	//Buffers
	AssetContainer<std::string, GraphicsBuffer> mBufferContainer;
	
	//Sprites
	AssetContainer<std::string, Sprite> mSpriteContainer;

	//Spritesheets
	AssetContainer<std::string, SpriteSheet> mSpriteSheetContainer;

	//Values
	AssetContainer<std::string, float> mValueContainer;

	//Colors
	AssetContainer<std::string, Color> mColorContainer;

	//Sounds
	AssetContainer<std::string, Sound> mSoundContainer;

	//Fonts
	AssetContainer<std::string, Font> mFontContainer;

	//Vector2D - Handles positions for saving, loading, and positioning
	AssetContainer<std::string, Vector2D> mVector2DContainer;

	void loadBuffers();
	void loadSprites();
	void loadSpriteSheets();
	void loadValues();
	void loadColors();
	void loadSounds();
	void loadFonts();
	void loadVector2Ds();
};

#endif