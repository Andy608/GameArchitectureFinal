/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef GRAPHICS_SYSTEM_H_
#define GRAPHICS_SYSTEM_H_

#include <Trackable.h>

struct ALLEGRO_DISPLAY;
struct ALLEGRO_COLOR;
class GraphicsBuffer;
class Sprite;
class Font;
struct Color;

class GraphicsSystem : public Trackable
{
	friend class InputSystem;
	friend class GraphicsBuffer;

public:
	static GraphicsSystem* getInstance();
	static bool initInstance(const int& displayWidth, const int& displayHeight);
	static void cleanupInstance();

	static const int getDisplayWidth();
	static const int getDisplayHeight();
	static const GraphicsBuffer& getBackBuffer();

	static void flip();

	static void draw(const int& startingX, const int& startingY, const GraphicsBuffer& buffer, const float& scale = 1.0f);
	static void draw(const GraphicsBuffer& targetBuffer, const int& startingX, const int& startingY, const GraphicsBuffer& buffer, const float& scale = 1.0f);

	static void drawRotated(const int& bitmapStartX, const int& bitmapStartY, const int& width, const int& height,
				const float& startingX, const float& startingY, const GraphicsBuffer& buffer, const float& degrees, const float& scale = 1.0f);

	static void drawCentered(const GraphicsBuffer& buffer, const float& scale = 1.0f);
	static void drawScaledToFit(const int& startingX, const int& startingY, const GraphicsBuffer& buffer, const float& width, const float& height);

	static void draw(const int& startingX, const int& startingY, const Sprite& sprite, const float& scale = 1.0f);
	static void draw(const GraphicsBuffer& targetBuffer, const int& startingX, const int& startingY, const Sprite& sprite, const float& scale = 1.0f);
	static void drawCentered(const Sprite& sprite, const float& scale = 1.0f);

	static void writeText(const int& startingX, const int& startingY, const Font& font, const Color& color, const std::string& text);
	static void writeText(const GraphicsBuffer& targetBuffer, const int& startingX, const int& startingY, const Font& font, const Color& color, const std::string& text);
	
	static void saveBuffer(const GraphicsBuffer& bufferToSave, const std::string& fileName);

	//Disable any form of copying for a GraphicsSystem object.
	GraphicsSystem(const GraphicsSystem& copy) = delete;
	void operator=(const GraphicsSystem& copy) = delete;

private:
	static GraphicsSystem* smpInstance;

	bool mIsInitialized;
	ALLEGRO_DISPLAY* mpDisplay;
	GraphicsBuffer* mpBackbuffer;

	static ALLEGRO_COLOR toAllegroColor(const Color& color);

	GraphicsSystem();
	~GraphicsSystem();

	bool init(const int& displayWidth, const int& displayHeight);
	void cleanup();
};

#endif