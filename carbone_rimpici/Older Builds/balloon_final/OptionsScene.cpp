#include "OptionsScene.h"
#include "Game.h"
#include "AssetManager.h"
#include "GraphicsSystem.h"
#include "SceneManager.h"
#include "SaveManager.h"
#include "Game.h"
#include <EventSystem.h>

void onOptionsSceneBackButtonClicked()
{
	Game::getInstance()->getSceneManager()->setCurrentScene(EnumScene::TITLE_SCENE);
}

void onOptionsSceneEnglishButtonClicked()
{
	Game::getInstance()->getLocalizationMap()->setCurrentLanguage(EnumLanguage::ENGLISH);
}

void onOptionsSceneFrenchButtonClicked()
{
	Game::getInstance()->getLocalizationMap()->setCurrentLanguage(EnumLanguage::FRENCH);
}

void onOptionsSceneSoundOnButtonClicked()
{
	Game::getInstance()->toggleSound(true);
}

void onOptionsSceneSoundOffButtonClicked()
{
	Game::getInstance()->toggleSound(false);
}

OptionsScene::OptionsScene() : Scene(EnumScene::OPTIONS_SCENE),
mMenuButtons(std::vector<UITextButton*>())
{
	const Font& buttonFont = *mpAssetManagerInstance->getFont("gui_font");
	const Color& defaultColor = *mpAssetManagerInstance->getColor("text_color");
	const Color& hoveredColor = *mpAssetManagerInstance->getColor("title_color");
	const Color& pressedColor = *mpAssetManagerInstance->getColor("button_press_color");

	UITextButton* backButton = new UITextButton(this, &onOptionsSceneBackButtonClicked, buttonFont, "options_scene_menu_back",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("options_scene_menu_back")).getX(),
		(int)*mpAssetManagerInstance->getValue("options_scene_menu_back_y"),
		defaultColor, hoveredColor, pressedColor);

	UITextButton* englishButton = new UITextButton(this, &onOptionsSceneEnglishButtonClicked, buttonFont, "options_scene_menu_english",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("options_scene_menu_english")).getX(),
		(int)*mpAssetManagerInstance->getValue("options_scene_menu_english_y"),
		defaultColor, hoveredColor, pressedColor);

	UITextButton* frenchButton = new UITextButton(this, &onOptionsSceneFrenchButtonClicked, buttonFont, "options_scene_menu_french",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("options_scene_menu_french")).getX(),
		(int)*mpAssetManagerInstance->getValue("options_scene_menu_french_y"),
		defaultColor, hoveredColor, pressedColor);

	UITextButton* soundOnButton = new UITextButton(this, &onOptionsSceneSoundOnButtonClicked, buttonFont, "options_scene_menu_sound_on",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("options_scene_menu_sound_on")).getX(),
		(int)*mpAssetManagerInstance->getValue("options_scene_menu_sound_on_y"),
		defaultColor, hoveredColor, pressedColor);

	UITextButton* soundOffButton = new UITextButton(this, &onOptionsSceneSoundOffButtonClicked, buttonFont, "options_scene_menu_sound_off",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("options_scene_menu_sound_off")).getX(),
		(int)*mpAssetManagerInstance->getValue("options_scene_menu_sound_off_y"),
		defaultColor, hoveredColor, pressedColor);

	backButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(backButton);

	englishButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(englishButton);

	frenchButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(frenchButton);

	soundOnButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(soundOnButton);

	soundOffButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(soundOffButton);
}

OptionsScene::~OptionsScene()
{
	cleanup();
}

void OptionsScene::start()
{
	for (UITextButton* menuButton : mMenuButtons)
	{
		if (menuButton)
		{
			menuButton->updateBounds();
		}
	}

	mIsInitialized = true;
}

void OptionsScene::end()
{

}

void OptionsScene::cleanup()
{
	for (UITextButton* menuButton : mMenuButtons)
	{
		if (menuButton)
		{
			delete menuButton;
		}
	}

	mMenuButtons.clear();

	mIsInitialized = false;
}

void OptionsScene::update(float deltaTime)
{
	for (UITextButton* menuButton : mMenuButtons)
	{
		menuButton->update(deltaTime);
	}
}

void OptionsScene::draw()
{
	GraphicsSystem::drawScaledToFit(0, 0, *mpAssetManagerInstance->getBuffer("background_buffer"), GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
	GraphicsSystem::writeTextCenteredHorizontally((int)*mpAssetManagerInstance->getValue("options_scene_menu_title_y"), *mpAssetManagerInstance->getFont("title_font"), *mpAssetManagerInstance->getColor("title_color"), mpLocalizationInstance->getLocalizedString("options_scene_menu_title"));
	GraphicsSystem::writeTextCenteredHorizontally((int)*mpAssetManagerInstance->getValue("options_scene_menu_languages_y"), *mpAssetManagerInstance->getFont("subtitle_font"), *mpAssetManagerInstance->getColor("title_color"), mpLocalizationInstance->getLocalizedString("options_scene_menu_languages"));
	GraphicsSystem::writeTextCenteredHorizontally((int)*mpAssetManagerInstance->getValue("options_scene_menu_sound_y"), *mpAssetManagerInstance->getFont("subtitle_font"), *mpAssetManagerInstance->getColor("title_color"), mpLocalizationInstance->getLocalizedString("options_scene_menu_sound"));



	for (UITextButton* menuButton : mMenuButtons)
	{
		menuButton->draw();
	}
}

void OptionsScene::save()
{
	SaveManager* saveManager = Game::getInstance()->getSaveManager();
	EnumLanguage language = Game::getInstance()->getLocalizationMap()->getLanguageType();
	saveManager->getSaveFile("options_save_data")->addSaveData("language", 
		LocalizationFile::enumToString(language));
}

void OptionsScene::load()
{
	
}