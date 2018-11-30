#ifndef UI_TEXT_BUTTON_H_
#define UI_TEXT_BUTTON_H_

#include <EventListener.h>
#include <Vector2D.h>
#include <Color.h>
#include <Font.h>
#include "RectBounds.h"
#include "LocalizationMap.h"
#include "Scene.h"

class UITextButton : public EventListener
{
public:
	UITextButton(Scene* scene, void(*onClick)(), const Font& buttonFont, std::string localizedID, int startingX, int startingY, Color normalColor = sDEFAULT_COLOR, Color hoveredColor = sDEFAULT_COLOR, Color pressedColor = sDEFAULT_COLOR);
	virtual ~UITextButton();

	virtual void update(float deltaTime);
	virtual void draw();

	virtual void handleEvent(const Event& theEvent);

	inline void shouldDrawCenteredHorizontally(bool drawCentered) { mDrawHorizontallyCentered = drawCentered; };
	inline void setPosition(int startingX, int startingY) { mPosition.setX((float)startingX); mPosition.setY((float)startingY); updateBounds(); };
	inline void setText(std::string localizedTextID) { mLocalizedTextID = localizedTextID; };

	void updateBounds();

	inline Vector2D getPosition() const { return mPosition; };
	RectBounds* getBounds();

private:
	static const Color sDEFAULT_COLOR;

	LocalizationMap* mpLocalizationInstance;
	Scene* mScene;
	void(*mOnButtonClicked)();


	Vector2D mPosition;
	std::string mLocalizedTextID;
	const Font& mFont;

	bool mDrawHorizontallyCentered;

	Color mCurrentColor;
	Color mNormalColor;
	Color mHoveredColor;
	Color mPressedColor;

	bool mIsPressed;

	RectBounds* mpRectBounds = nullptr;
};

#endif