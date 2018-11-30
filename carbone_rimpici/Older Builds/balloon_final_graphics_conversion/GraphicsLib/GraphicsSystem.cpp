/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <iostream>
#include <cassert>
#include <string>

#include "GraphicsSystem.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"
#include "Font.h"
#include "Color.h"

GraphicsSystem* GraphicsSystem::smpInstance = nullptr;

GraphicsSystem* GraphicsSystem::getInstance()
{
	assert(smpInstance);
	return smpInstance;
}

bool GraphicsSystem::initInstance(const int& displayWidth, const int& displayHeight)
{
	if (!smpInstance)
	{
		std::cout << "Game instance is null, creating new instance." << std::endl;
		smpInstance = new GraphicsSystem();
	}

	return smpInstance->init(displayWidth, displayHeight);
}

void GraphicsSystem::cleanupInstance()
{
	delete smpInstance;
	smpInstance = nullptr;
}

GraphicsSystem::GraphicsSystem() :
	mIsInitialized(false),
	mpDisplay(nullptr),
	mpBackbuffer(nullptr)
{

}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

bool GraphicsSystem::init(const int& displayWidth, const int& displayHeight)
{
	if (!mIsInitialized)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "There was an error initializing SDL: " << SDL_GetError() << std::endl;
			cleanup();
			return false;
		}


		if (!IMG_Init(IMG_INIT_PNG) && IMG_INIT_PNG)
		{
			std::cout << "Error initializing SDL_Image for PNG file: " << IMG_GetError() << std::endl;
			cleanup();
			return false;
		}

		mpDisplay = SDL_CreateWindow("Hello, World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, displayWidth, displayHeight, SDL_WINDOW_ALLOW_HIGHDPI);
		
		if (!mpDisplay)
		{
			std::cout << "Error initializing SDL window: " << SDL_GetError() << std::endl;
			cleanup();
			return false;
		}

		mpRenderer = SDL_CreateRenderer(mpDisplay, -1, SDL_RENDERER_ACCELERATED);

		if (!mpRenderer)
		{
			std::cout << "Error initializing SDL window renderer: " << SDL_GetError() << std::endl;
			cleanup();
			return false;
		}

		mpBackbuffer = new GraphicsBuffer(SDL_GetWindowSurface(mpDisplay));
		mIsInitialized = true;
	}

	return mIsInitialized;
}

void GraphicsSystem::cleanup()
{
	if (mpDisplay)
	{
		SDL_DestroyWindow(mpDisplay);
		mpDisplay = nullptr;
	}

	if (mpBackbuffer)
	{
		delete mpBackbuffer;
		mpBackbuffer = nullptr;
	}

	if (mIsInitialized)
	{
		SDL_Quit();
	}
}

const int GraphicsSystem::getDisplayWidth()
{
	return SDL_GetWindowSurface(smpInstance->mpDisplay)->w;
}

const int GraphicsSystem::getDisplayHeight()
{
	return SDL_GetWindowSurface(smpInstance->mpDisplay)->h;
}

void GraphicsSystem::flip()
{
	SDL_RenderPresent(smpInstance->mpRenderer);
	SDL_RenderClear(smpInstance->mpRenderer);
}

void GraphicsSystem::draw(const int& drawingX, const int& drawingY, const GraphicsBuffer& buffer, const float& scale)
{
	draw(*smpInstance->mpBackbuffer, drawingX, drawingY, buffer, scale);
}

void GraphicsSystem::draw(const GraphicsBuffer& targetBuffer, const int& drawingX, const int& drawingY, const GraphicsBuffer& buffer, const float& scale)
{
	const int& BUFFER_WIDTH = buffer.getWidth();
	const int& BUFFER_HEIGHT = buffer.getHeight();
	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, targetBuffer.mpBitmapTexture);

	SDL_Rect gdSprite;

	gdSprite.x = drawingX;
	gdSprite.y = drawingY;
	gdSprite.w = BUFFER_WIDTH;
	gdSprite.h = BUFFER_HEIGHT;

	SDL_RenderCopy(smpInstance->mpRenderer, buffer.mpBitmapTexture, nullptr, &gdSprite);

	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
}

void GraphicsSystem::draw(const int& drawingX, const int& drawingY, SDL_Surface& surface, const float& scale)
{
	draw(*smpInstance->mpBackbuffer, drawingX, drawingY, surface, scale);
}

void GraphicsSystem::draw(const GraphicsBuffer& targetBuffer, const int& drawingX, const int& drawingY,
	SDL_Surface& surface, const float& scale)
{
	const int& SURFACE_WIDTH = surface.w;
	const int& SURFACE_HEIGHT = surface.h;

	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, targetBuffer.mpBitmapTexture);

	SDL_Texture* textureText = SDL_CreateTextureFromSurface(smpInstance->mpRenderer, &surface);

	SDL_Rect gdSprite;

	gdSprite.x = drawingX;
	gdSprite.y = drawingY;
	gdSprite.w = SURFACE_WIDTH;
	gdSprite.h = SURFACE_HEIGHT;

	SDL_RenderCopy(smpInstance->mpRenderer, textureText, nullptr, &gdSprite);
	
	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
}

void GraphicsSystem::drawCentered(const GraphicsBuffer& buffer, const float& scale)
{
	int centerX = (int)((getDisplayWidth() - buffer.getWidth() * scale) / 2.0f);
	int centerY = (int)((getDisplayHeight() - buffer.getHeight() * scale) / 2.0f);

	draw(centerX, centerY, buffer, scale);
}

void GraphicsSystem::drawRotated(const int& bitmapStartX, const int& bitmapStartY, const int& width, const int& height, const int& drawingX, const int& drawingY, const GraphicsBuffer& buffer, const float& degrees, const float& scale)
{
	const int& BUFFER_WIDTH = buffer.getWidth();
	const int& BUFFER_HEIGHT = buffer.getHeight();
	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, smpInstance->mpBackbuffer->mpBitmapTexture);
	//THIS NEEDS TO CHANGE SO WE CAN USE POSITIONS
	/*al_draw_tinted_scaled_rotated_bitmap_region(
		buffer.mpBitmapTexture,
		bitmapStartX, bitmapStartY, width, height,      // source bitmap region
		al_map_rgb(255, 255, 255),						// color, just use white if you don't want a tint
		width / 2, height / 2,							// center of rotation/scaling
		startingX, startingY,							// destination
		scale, scale,									// scale
		degrees * 3.14159 / 180.0, 0);					// angle and flags
		*/

	SDL_Point* center = new SDL_Point(SDL_Point{ (width / 2), (height / 2) });
	SDL_Rect gdSprite;

	gdSprite.x = drawingX;
	gdSprite.y = drawingY;
	gdSprite.w = width;
	gdSprite.h = height;

	SDL_RenderCopy(smpInstance->mpRenderer, buffer.mpBitmapTexture, nullptr, &gdSprite);
	SDL_RenderCopyEx(smpInstance->mpRenderer,
		buffer.mpBitmapTexture,
		nullptr, &gdSprite,
		(double)degrees,
		center,
		SDL_FLIP_NONE);

	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
}

void GraphicsSystem::drawScaledToFit(const int& drawingX, const int& drawingY, const GraphicsBuffer& buffer, const int& width, const int& height)
{
	float xScale = width / static_cast<float>(buffer.getWidth());
	float yScale = height / static_cast<float>(buffer.getHeight());

	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, smpInstance->mpBackbuffer->mpBitmapTexture);

	SDL_Rect gdSprite;

	gdSprite.x = drawingX;
	gdSprite.y = drawingY;
	gdSprite.w = width * xScale;
	gdSprite.h = height * yScale;

	//al_draw_scaled_bitmap(buffer.mpBitmapTexture, 0, 0, buffer.getWidth(), buffer.getHeight(), startingX, startingY, buffer.getWidth() * xScale, buffer.getHeight() * yScale, 0);
	//THIS NEEDS TO CHANGE SO WE CAN USE POSITIONS
	SDL_RenderCopy(smpInstance->mpRenderer, buffer.mpBitmapTexture, nullptr, &gdSprite);

	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
}

void GraphicsSystem::draw(const int& drawingX, const int& drawingY, const Sprite& sprite, const float& scale)
{
	draw(*smpInstance->mpBackbuffer, drawingX, drawingY, sprite, scale);
}

void GraphicsSystem::draw(const GraphicsBuffer& targetBuffer, const int& drawingX, const int& drawingY, const Sprite& sprite, const float& scale)
{
	GraphicsBuffer spriteBuffer = sprite.mSPRITE_BUFFER;

	const int& BUFFER_WIDTH = spriteBuffer.getWidth();
	const int& BUFFER_HEIGHT = spriteBuffer.getHeight();
	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, targetBuffer.mpBitmapTexture);

	SDL_Rect gdSprite;

	gdSprite.x = drawingX;
	gdSprite.y = drawingY;
	gdSprite.w = BUFFER_WIDTH;
	gdSprite.h = BUFFER_HEIGHT;

	SDL_RenderCopy(smpInstance->mpRenderer, spriteBuffer.mpBitmapTexture, nullptr, &gdSprite);

	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
}

void GraphicsSystem::drawCentered(const Sprite& sprite, const float& scale)
{
	int centerX = (int)((getDisplayWidth() - sprite.getWidth() * scale) / 2.0f);
	int centerY = (int)((getDisplayHeight() - sprite.getHeight() * scale) / 2.0f);

	draw(centerX, centerY, sprite, scale);
}

void GraphicsSystem::writeText(const int& startingX, const int& startingY, const Font& font, const Color& color, const std::string& text)
{
	writeText(*smpInstance->mpBackbuffer, startingX, startingY, font, color, text);
}

void GraphicsSystem::writeText(const GraphicsBuffer& targetBuffer, const int& startingX, const int& startingY, const Font& font, 
	const Color& color, const std::string& text)
{
	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, smpInstance->mpBackbuffer->mpBitmapTexture);

	SDL_Surface* surfaceText = TTF_RenderText_Solid(font.getFont(), text.c_str(), toSDLColor(color));
	draw(startingX, startingY, surfaceText);

	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
}

void GraphicsSystem::saveBuffer(const GraphicsBuffer& bufferToSave, const std::string& fileName)
{
	SDL_SaveBMP(bufferToSave.mpBitmapSurface, fileName.c_str());
}

const GraphicsBuffer& GraphicsSystem::getBackBuffer()
{
	return *smpInstance->mpBackbuffer;
}

SDL_Color GraphicsSystem::toSDLColor(const Color& color)
{
	SDL_Color c;
	c.r = color.red;
	c.g = color.green;
	c.b = color.blue;
	c.a = color.alpha;
	return c;
}