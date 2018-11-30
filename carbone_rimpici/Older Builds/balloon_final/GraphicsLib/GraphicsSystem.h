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

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Color;
struct SDL_Surface;
class GraphicsBuffer;
class Sprite;
class Font;
class Vector2D;
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

	//drawing with GraphicsBuffer as source
	static void draw(const int& drawingX, const int& drawingY, const GraphicsBuffer& buffer, const float& scale = 1.0f);
	static void draw(const GraphicsBuffer& targetBuffer, const int& drawingX, const int& drawingY, const GraphicsBuffer& buffer, const float& scale = 1.0f);

	//drawing with Texture as source
	static void draw(const int& drawingX, const int& drawingY, GraphicsBuffer& imageBuffer, const float& scale = 1.0f);
	
	static void draw(const GraphicsBuffer& targetBuffer, const int& drawingX, const int& drawingY, GraphicsBuffer& imageBuffer, const float& scale = 1.0f);

	//drawing with GraphicsBuffer as source and transform it in some way
	static void drawRotated(const int& bitmapStartX, const int& bitmapStartY, const int& width, const int& height,
							const int& drawingX, const int& drawingY, const GraphicsBuffer& buffer, const float& degrees, const float& scale = 1.0f);
	static void drawCentered(const GraphicsBuffer& buffer, const float& scale = 1.0f);
	static void drawScaledToFit(const int& drawingX, const int& drawingY, const GraphicsBuffer& buffer, const int& width, const int& height);

	//drawing with Sprite as source
	static void draw(const int& drawingX, const int& drawingY, const Sprite& sprite, const float& scale = 1.0f);
	static void draw(const GraphicsBuffer& targetBuffer, const int& drawingX, const int& drawingY, const Sprite& sprite, const float& scale = 1.0f);
	static void drawCentered(const Sprite& sprite, const float& scale = 1.0f);


	static void writeTextCenteredVertically(const int& startingY, const Font& font, const Color& color, const std::string& text);
	static void writeTextCenteredHorizontally(const int& startingX, const Font& font, const Color& color, const std::string& text);
	static void writeTextCentered(const Font& font, const Color& color, const std::string& text);
	static void writeText(const int& startingX, const int& startingY, const Font& font, const Color& color, const std::string& text);
	static void writeText(const GraphicsBuffer& targetBuffer, const int& startingX, const int& startingY, const Font& font, const Color& color, const std::string& text);
	
	static Vector2D getCenteredTextPosition(const Font& font, const std::string& text);

	static void saveBuffer(const GraphicsBuffer& bufferToSave, const std::string& fileName);

	//Disable any form of copying for a GraphicsSystem object.
	GraphicsSystem(const GraphicsSystem& copy) = delete;
	void operator=(const GraphicsSystem& copy) = delete;

	inline SDL_Renderer* getRenderer() const { return mpRenderer; };

private:
	static GraphicsSystem* smpInstance;

	bool mIsInitialized;
	SDL_Renderer* mpRenderer;
	SDL_Window* mpDisplay;
	GraphicsBuffer* mpBackbuffer;

	static SDL_Color toSDLColor(const Color& color);

	GraphicsSystem();
	~GraphicsSystem();

	bool init(const int& displayWidth, const int& displayHeight);
	void cleanup();
};

#endif