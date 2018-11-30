#include "UITextButton.h"
#include <EventSystem.h>
#include <InputSystem.h>
#include <GraphicsSystem.h>
#include "Game.h"
#include "GameEvent.h"
#include "LocalizationMap.h"
#include "SceneManager.h"

const Color UITextButton::sDEFAULT_COLOR = Color(255, 255, 255);

UITextButton::UITextButton(Scene* scene, void(*onClick)(), const Font& buttonFont, std::string localizedID, int startingX, int startingY,
	Color normalColor, Color hoveredColor, Color pressedColor) :
	
	EventListener(EventSystem::getInstance()),
	mpLocalizationInstance(Game::getInstance()->getLocalizationMap()),
	mFont(buttonFont),
	mLocalizedTextID(localizedID),
	mPosition(Vector2D(startingX, startingY)),
	mCurrentColor(normalColor),
	mNormalColor(normalColor),
	mHoveredColor(hoveredColor),
	mPressedColor(pressedColor),
	mpRectBounds(getBounds()),
	mOnButtonClicked(onClick),
	mScene(scene),
	mIsPressed(false)
{
	EventListener::getEventSystem()->addListener(Event::EnumEventType::_MOUSE_EVENT, this);
	EventListener::getEventSystem()->addListener((Event::EnumEventType)GameEvent::EnumGameEventType::_LANGUAGE_CHANGED_EVENT, this);
}

UITextButton::~UITextButton()
{
	if (mpRectBounds)
	{
		delete mpRectBounds;
		mpRectBounds = nullptr;
	}
}

void UITextButton::update(float deltaTime)
{
	if (mIsPressed)
	{
		mOnButtonClicked();
		mIsPressed = false;
	}
}

void UITextButton::draw()
{
	GraphicsSystem::writeText(mPosition.getX(), mPosition.getY(), mFont, mCurrentColor, mpLocalizationInstance->getLocalizedString(mLocalizedTextID));
}

typedef void(*fudnc);

void UITextButton::handleEvent(const Event& theEvent)
{
	if (mScene->getSceneType() != Game::getInstance()->getSceneManager()->getCurrentSceneType())
	{
		return;
	}

	if (theEvent.getType() == Event::EnumEventType::_MOUSE_EVENT)
	{
		const MouseEvent& mouseEvent = static_cast<const MouseEvent&>(theEvent);

		if (getBounds()->isPointInBounds(mouseEvent.getMousePosition()))
		{
			if (mouseEvent.isMouseDown())
			{
				mCurrentColor = mPressedColor;
			}
			else if (mCurrentColor == mPressedColor && !mouseEvent.isMouseDown())
			{
				mIsPressed = true;
				mCurrentColor = mNormalColor;
			}
			else
			{
				mCurrentColor = mHoveredColor;
			}
		}
		else
		{
			mCurrentColor = mNormalColor;
		}
	}
	else if (theEvent.getType() == GameEvent::EnumGameEventType::_LANGUAGE_CHANGED_EVENT)
	{
		updateBounds();
	}
}

RectBounds* UITextButton::getBounds()
{
	if (!mpRectBounds)
	{
		Vector2D buttonDimensions = Font::getDimensions(mFont, mpLocalizationInstance->getLocalizedString(mLocalizedTextID));
		mpRectBounds = new RectBounds((int)mPosition.getX(), (int)mPosition.getY(), (int)buttonDimensions.getX(), (int)buttonDimensions.getY());
	}
	
	return mpRectBounds;
}

void UITextButton::updateBounds()
{
	Vector2D buttonDimensions = Font::getDimensions(mFont, mpLocalizationInstance->getLocalizedString(mLocalizedTextID));

	if (mDrawHorizontallyCentered)
	{
		mPosition.setX(GraphicsSystem::getCenteredTextPosition(mFont, mpLocalizationInstance->getLocalizedString(mLocalizedTextID)).getX());
	}

	mpRectBounds->updateBounds((int)mPosition.getX(), (int)mPosition.getY(), (int)buttonDimensions.getX(), (int)buttonDimensions.getY());
}
