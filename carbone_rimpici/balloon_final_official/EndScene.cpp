/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "EndScene.h"
#include "Game.h"
#include "AssetManager.h"
#include "GraphicsSystem.h"
#include "SceneManager.h"
#include "Game.h"
#include <EventSystem.h>

void onEndSceneBackButtonClicked()
{
	Game::getInstance()->getSceneManager()->setCurrentScene(EnumScene::TITLE_SCENE);
}

EndScene::EndScene() : Scene(EnumScene::TITLE_SCENE),
mMenuButtons(std::vector<UITextButton*>())
{
	const Font& buttonFont = *mpAssetManagerInstance->getFont("gui_font");
	const Color& defaultColor = *mpAssetManagerInstance->getColor("text_color");
	const Color& hoveredColor = *mpAssetManagerInstance->getColor("title_color");
	const Color& pressedColor = *mpAssetManagerInstance->getColor("button_press_color");

	UITextButton* backButton = new UITextButton(this, &onEndSceneBackButtonClicked, buttonFont, "end_scene_menu_back",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("end_scene_menu_back")).getX(),
		(int)*mpAssetManagerInstance->getValue("end_scene_menu_back_y"),
		defaultColor, hoveredColor, pressedColor);

	backButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(backButton);
}

EndScene::~EndScene()
{
	cleanup();
}

void EndScene::start()
{
	for (UITextButton* menuButton : mMenuButtons)
	{
		if (menuButton)
		{
			menuButton->setPressed(false);
			menuButton->updateBounds();
		}
	}

	mIsInitialized = true;
}

void EndScene::end() {}

void EndScene::cleanup()
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

void EndScene::update(float deltaTime)
{
	for (UITextButton* menuButton : mMenuButtons)
	{
		menuButton->update(deltaTime);
	}
}

void EndScene::draw()
{
	GraphicsSystem::drawScaledToFit(0, 0, *mpAssetManagerInstance->getBuffer("background_buffer"), GraphicsSystem::getDisplayWidth(), GraphicsSystem::getDisplayHeight());
	GraphicsSystem::writeTextCenteredHorizontally(*mpAssetManagerInstance->getValue("end_scene_menu_title_y"), *mpAssetManagerInstance->getFont("title_font"), *mpAssetManagerInstance->getColor("title_color"), mpLocalizationInstance->getLocalizedString("end_scene_menu_title"));
	GraphicsSystem::writeTextCenteredHorizontally(*mpAssetManagerInstance->getValue("end_scene_menu_subtitle_y"), *mpAssetManagerInstance->getFont("gui_font"), *mpAssetManagerInstance->getColor("text_color"), mpLocalizationInstance->getLocalizedString("end_scene_menu_subtitle") + " " + std::to_string(Game::getInstance()->getScore()));

	for (UITextButton* menuButton : mMenuButtons)
	{
		menuButton->draw();
	}
}

void EndScene::save() {}

void EndScene::load() {}