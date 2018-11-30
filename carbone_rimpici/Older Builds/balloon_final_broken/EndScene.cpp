#include "EndScene.h"
#include "Game.h"
#include "AssetManager.h"
#include "GraphicsSystem.h"
#include "SceneManager.h"
#include "Game.h"
#include <EventSystem.h>

void onEndSceneBackButtonClicked()
{
	EventSystem::fireEvent(Event::EnumEventType::_QUIT_EVENT);
}

EndScene::EndScene() : Scene(EnumScene::TITLE_SCENE),
mMenuButtons(std::vector<UITextButton*>())
{
	const Font& buttonFont = *mpAssetManagerInstance->getFont("gui_font");
	const Color& defaultColor = *mpAssetManagerInstance->getColor("text_color");
	const Color& hoveredColor = *mpAssetManagerInstance->getColor("title_color");
	const Color& pressedColor = *mpAssetManagerInstance->getColor("button_press_color");

	UITextButton* backGameButton = new UITextButton(this, &onEndSceneBackButtonClicked, buttonFont, "title_scene_menu_start",
		(int)GraphicsSystem::getCenteredTextPosition(buttonFont, mpLocalizationInstance->getLocalizedString("title_scene_menu_start")).getX(),
		(int)*mpAssetManagerInstance->getValue("title_scene_menu_start_y"),
		defaultColor, hoveredColor, pressedColor);

	backGameButton->shouldDrawCenteredHorizontally(true);
	mMenuButtons.push_back(backGameButton);
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
			menuButton->updateBounds();
		}
	}

	mIsInitialized = true;
}

void EndScene::end()
{

}

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
	GraphicsSystem::writeTextCenteredHorizontally(*mpAssetManagerInstance->getValue("title_scene_menu_title_y"), *mpAssetManagerInstance->getFont("title_font"), *mpAssetManagerInstance->getColor("title_color"), mpLocalizationInstance->getLocalizedString("title_scene_menu_title"));
	GraphicsSystem::writeTextCenteredHorizontally(*mpAssetManagerInstance->getValue("title_scene_menu_subtitle_y"), *mpAssetManagerInstance->getFont("gui_font"), *mpAssetManagerInstance->getColor("text_color"), mpLocalizationInstance->getLocalizedString("title_scene_menu_subtitle"));

	for (UITextButton* menuButton : mMenuButtons)
	{
		menuButton->draw();
	}
}

void EndScene::save()
{

}

void EndScene::load()
{

}