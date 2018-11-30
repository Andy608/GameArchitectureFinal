#include "TitleScene.h"
#include "Game.h"
#include "AssetManager.h"
#include "GraphicsSystem.h"
#include "SceneManager.h"
#include "Game.h"
#include <EventSystem.h>
#include "SaveManager.h"

void onTitleSceneStartButtonClicked()
{
	Game::getInstance()->getSaveManager()->getSaveFile("game_save_data")->deleteSaveData();
	Game::getInstance()->getSceneManager()->setCurrentScene(EnumScene::GAME_SCENE);
}

void onTitleSceneLoadButtonClicked()
{
	Game::getInstance()->getSceneManager()->setCurrentScene(EnumScene::GAME_SCENE);
}

void onTitleSceneOptionsButtonClicked()
{
	Game::getInstance()->getSceneManager()->setCurrentScene(EnumScene::OPTIONS_SCENE);
}

void onTitleSceneExitButtonClicked()
{
	EventSystem::fireEvent(Event::EnumEventType::_QUIT_EVENT);
}

TitleScene::TitleScene() : Scene(EnumScene::TITLE_SCENE),
	mMenuButtons(std::vector<UITextButton*>())
{
	const Font& buttonFont = *mpAssetManagerInstance->getFont("gui_font");
	const Color& defaultColor = *mpAssetManagerInstance->getColor("text_color");
	const Color& hoveredColor = *mpAssetManagerInstance->getColor("title_color");
	const Color& pressedColor = *mpAssetManagerInstance->getColor("button_press_color");

	UITextButton* startGameButton = new UITextButton(this, &onTitleSceneStartButtonClicked, buttonFont, "title_scene_menu_start",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("title_scene_menu_start")).getX(),
		(int)*mpAssetManagerInstance->getValue("title_scene_menu_start_y"),
		defaultColor, hoveredColor, pressedColor);

	UITextButton* loadGameButton = new UITextButton(this, &onTitleSceneLoadButtonClicked, buttonFont, "title_scene_menu_load",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("title_scene_menu_load")).getX(),
		(int)*mpAssetManagerInstance->getValue("title_scene_menu_load_y"),
		defaultColor, hoveredColor, pressedColor);
	
	UITextButton* optionsButton = new UITextButton(this, &onTitleSceneOptionsButtonClicked, buttonFont, "title_scene_menu_options",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("title_scene_menu_options")).getX(),
		(int)*mpAssetManagerInstance->getValue("title_scene_menu_options_y"),
		defaultColor, hoveredColor, pressedColor);
	
	UITextButton* exitButton = new UITextButton(this, &onTitleSceneExitButtonClicked, buttonFont, "title_scene_menu_exit",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("title_scene_menu_exit")).getX(),
		(int)*mpAssetManagerInstance->getValue("title_scene_menu_exit_y"),
		defaultColor, hoveredColor, pressedColor);

	startGameButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(startGameButton);

	loadGameButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(loadGameButton);

	optionsButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(optionsButton);

	exitButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(exitButton);
}

TitleScene::~TitleScene()
{
	cleanup();
}

void TitleScene::start()
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

void TitleScene::end()
{
	
}

void TitleScene::cleanup()
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

void TitleScene::update(float deltaTime)
{
	for (UITextButton* menuButton : mMenuButtons)
	{
		menuButton->update(deltaTime);
	}
}

void TitleScene::draw()
{
	GraphicsSystem::drawScaledToFit(0, 0, *mpAssetManagerInstance->getBuffer("background_buffer"), GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
	GraphicsSystem::writeTextCenteredHorizontally(*mpAssetManagerInstance->getValue("title_scene_menu_title_y"), *mpAssetManagerInstance->getFont("title_font"), *mpAssetManagerInstance->getColor("title_color"), mpLocalizationInstance->getLocalizedString("title_scene_menu_title"));
	GraphicsSystem::writeTextCenteredHorizontally(*mpAssetManagerInstance->getValue("title_scene_menu_subtitle_y"), *mpAssetManagerInstance->getFont("gui_font"), *mpAssetManagerInstance->getColor("text_color"), mpLocalizationInstance->getLocalizedString("title_scene_menu_subtitle"));

	for (UITextButton* menuButton : mMenuButtons)
	{
		menuButton->draw();
	}
}

void TitleScene::save()
{

}

void TitleScene::load()
{
}