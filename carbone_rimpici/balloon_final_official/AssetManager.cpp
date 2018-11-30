/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "AssetManager.h"

AssetManager::AssetManager(SettingsFile& mainSettingsFile) :
	mMainSettingsFile(mainSettingsFile),
	mIsLoaded(false)
{

}

GraphicsBuffer* AssetManager::getBuffer(std::string key) const
{
	try
	{
		return mBufferContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Sprite* AssetManager::getSprite(std::string key) const
{
	try
	{
		return mSpriteContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

SpriteSheet* AssetManager::getSpriteSheet(std::string key) const
{
	try
	{
		return mSpriteSheetContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

float* AssetManager::getValue(std::string key) const
{
	try
	{
		return mValueContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Color* AssetManager::getColor(std::string key) const
{
	try
	{
		return mColorContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Sound* AssetManager::getSound(std::string key) const
{
	try
	{
		return mSoundContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Font* AssetManager::getFont(std::string key) const
{
	try
	{
		return mFontContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

Vector2D* AssetManager::getVector2D(std::string key) const
{
	try
	{
		return mVector2DContainer.getAsset(key);
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

bool AssetManager::loadAssets()
{
	bool success;

	if (!mIsLoaded)
	{
		try
		{
			loadValues();
			loadBuffers();
			loadSprites();
			loadSpriteSheets();
			loadColors();
			loadSounds();
			loadFonts();
			loadVector2Ds();
			success = true;
		}
		catch (const std::exception& e)
		{
			success = false;
			std::cout << "Unable to load asset from file. Error: " << e.what() << std::endl;
		}

		if (success)
		{
			mIsLoaded = true;
		}
	}

	return success;
}

void AssetManager::loadBuffers()
{
	mBufferContainer.addAsset("background_buffer", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("background_buffer")));
	mBufferContainer.addAsset("air_balloon", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("air_balloon_buffer")));
	mBufferContainer.addAsset("wall", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("wall_buffer")));
	mBufferContainer.addAsset("balloon_wall", new GraphicsBuffer(mMainSettingsFile.getSettingFromKey("balloon_wall_buffer")));
}

void AssetManager::loadSprites()
{
	mSpriteContainer.addAsset("player_sprite", new Sprite(*mBufferContainer.getAsset("air_balloon")));
	mSpriteContainer.addAsset("wall_sprite", new Sprite(*mBufferContainer.getAsset("wall")));
}

void AssetManager::loadSpriteSheets()
{
	mSpriteSheetContainer.addAsset("balloon_wall_spritesheet", new SpriteSheet(*mBufferContainer.getAsset("balloon_wall"), (int)*getValue("balloon_wall_sheet_row_amount"), (int)*getValue("balloon_wall_sheet_column_amount")));
}

void AssetManager::loadValues()
{
	mValueContainer.addAsset("title_color_r", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_color_r"))));
	mValueContainer.addAsset("title_color_g", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_color_g"))));
	mValueContainer.addAsset("title_color_b", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_color_b"))));

	mValueContainer.addAsset("text_color_r", new float(std::stof(mMainSettingsFile.getSettingFromKey("text_color_r"))));
	mValueContainer.addAsset("text_color_g", new float(std::stof(mMainSettingsFile.getSettingFromKey("text_color_g"))));
	mValueContainer.addAsset("text_color_b", new float(std::stof(mMainSettingsFile.getSettingFromKey("text_color_b"))));

	mValueContainer.addAsset("button_press_color_r", new float(std::stof(mMainSettingsFile.getSettingFromKey("button_press_color_r"))));
	mValueContainer.addAsset("button_press_color_g", new float(std::stof(mMainSettingsFile.getSettingFromKey("button_press_color_g"))));
	mValueContainer.addAsset("button_press_color_b", new float(std::stof(mMainSettingsFile.getSettingFromKey("button_press_color_b"))));

	mValueContainer.addAsset("title_font_size", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_font_size"))));
	mValueContainer.addAsset("subtitle_font_size", new float(std::stof(mMainSettingsFile.getSettingFromKey("subtitle_font_size"))));
	mValueContainer.addAsset("gui_font_size", new float(std::stof(mMainSettingsFile.getSettingFromKey("gui_font_size"))));

	mValueContainer.addAsset("score_location_x", new float(std::stof(mMainSettingsFile.getSettingFromKey("score_location_x"))));
	mValueContainer.addAsset("score_location_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("score_location_y"))));

	mValueContainer.addAsset("score_update_timing", new float(std::stof(mMainSettingsFile.getSettingFromKey("score_update_timing"))));
	mValueContainer.addAsset("score_difficulty_change", new float(std::stof(mMainSettingsFile.getSettingFromKey("score_difficulty_change"))));

	mValueContainer.addAsset("title_scene_menu_title_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_title_y"))));
	mValueContainer.addAsset("title_scene_menu_subtitle_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_subtitle_y"))));
	mValueContainer.addAsset("title_scene_menu_start_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_start_y"))));
	mValueContainer.addAsset("title_scene_menu_load_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_load_y"))));
	mValueContainer.addAsset("title_scene_menu_options_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_options_y"))));
	mValueContainer.addAsset("title_scene_menu_exit_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("title_scene_menu_exit_y"))));

	mValueContainer.addAsset("options_scene_menu_title_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_title_y"))));
	mValueContainer.addAsset("options_scene_menu_back_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_back_y"))));
	mValueContainer.addAsset("options_scene_menu_sound_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_sound_y"))));
	mValueContainer.addAsset("options_scene_menu_sound_on_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_sound_on_y"))));
	mValueContainer.addAsset("options_scene_menu_sound_off_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_sound_off_y"))));

	mValueContainer.addAsset("options_scene_menu_languages_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_languages_y"))));
	mValueContainer.addAsset("options_scene_menu_english_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_english_y"))));
	mValueContainer.addAsset("options_scene_menu_french_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_french_y"))));
	mValueContainer.addAsset("options_scene_menu_spanish_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("options_scene_menu_spanish_y"))));

	mValueContainer.addAsset("end_scene_menu_title_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("end_scene_menu_title_y"))));
	mValueContainer.addAsset("end_scene_menu_subtitle_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("end_scene_menu_subtitle_y"))));
	mValueContainer.addAsset("end_scene_menu_back_y", new float(std::stof(mMainSettingsFile.getSettingFromKey("end_scene_menu_back_y"))));

	mValueContainer.addAsset("starting_acceleration_x", new float(std::stof(mMainSettingsFile.getSettingFromKey("starting_acceleration_x"))));
	mValueContainer.addAsset("starting_velocity_x", new float(std::stof(mMainSettingsFile.getSettingFromKey("starting_velocity_x"))));
	
	mValueContainer.addAsset("starting_balloon_wall_velocity", new float(std::stof(mMainSettingsFile.getSettingFromKey("starting_balloon_wall_velocity"))));

	mValueContainer.addAsset("difficulty_block_initial_velocity", new float(std::stof(mMainSettingsFile.getSettingFromKey("difficulty_block_initial_velocity"))));
	mValueContainer.addAsset("difficulty_block_increment_velocity", new float(std::stof(mMainSettingsFile.getSettingFromKey("difficulty_block_increment_velocity"))));

	mValueContainer.addAsset("balloon_wall_sheet_row_amount", new float(std::stof(mMainSettingsFile.getSettingFromKey("balloon_wall_sheet_row_amount"))));
	mValueContainer.addAsset("balloon_wall_sheet_column_amount", new float(std::stof(mMainSettingsFile.getSettingFromKey("balloon_wall_sheet_column_amount"))));

	mValueContainer.addAsset("difficulty_frequency_scale", new float(std::stof(mMainSettingsFile.getSettingFromKey("difficulty_frequency_scale"))));
	mValueContainer.addAsset("difficulty_amplitude_scale", new float(std::stof(mMainSettingsFile.getSettingFromKey("difficulty_amplitude_scale"))));
}

void AssetManager::loadColors()
{
	mColorContainer.addAsset("title_color", new Color((unsigned char)*getValue("title_color_r"),
		(unsigned char)*getValue("title_color_g"), (unsigned char)*getValue("title_color_b")));

	mColorContainer.addAsset("text_color", new Color((unsigned char)*getValue("text_color_r"),
		(unsigned char)*getValue("text_color_g"), (unsigned char)*getValue("text_color_b")));

	mColorContainer.addAsset("button_press_color", new Color((unsigned char)*getValue("button_press_color_r"),
		(unsigned char)*getValue("button_press_color_g"), (unsigned char)*getValue("button_press_color_b")));
}

void AssetManager::loadSounds()
{
	mSoundContainer.addAsset("balloon_sound", new Sound(mMainSettingsFile.getSettingFromKey("balloon_sound_filename"), true));
	mSoundContainer.addAsset("balloon_music", new Sound(mMainSettingsFile.getSettingFromKey("balloon_music_filename"), false));
}

void AssetManager::loadFonts()
{
	mFontContainer.addAsset("title_font", new Font(mMainSettingsFile.getSettingFromKey("font_src"), (int)*getValue("title_font_size")));
	mFontContainer.addAsset("subtitle_font", new Font(mMainSettingsFile.getSettingFromKey("font_src"), (int)*getValue("subtitle_font_size")));
	mFontContainer.addAsset("gui_font", new Font(mMainSettingsFile.getSettingFromKey("font_src"), (int)*getValue("gui_font_size")));
}

void AssetManager::loadVector2Ds()
{
	mVector2DContainer.addAsset("score_location", new Vector2D((float)*getValue("score_location_x"),
		(float)*getValue("score_location_y")));
}