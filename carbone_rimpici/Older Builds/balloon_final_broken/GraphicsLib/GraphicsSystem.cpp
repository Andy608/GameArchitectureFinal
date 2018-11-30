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
#include <SDL_mixer.h>

#include <iostream>
#include <cassert>
#include <string>
#include <Vector2D.h>

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

		if (TTF_Init() < 0)
		{
			std::cout << "There was an error initializing TTF: " << TTF_GetError() << std::endl;
			cleanup();
			return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << std::endl;
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
		Mix_Quit();
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

void GraphicsSystem::draw(const float& drawingX, const float& drawingY, const GraphicsBuffer& buffer, const float& scale)
{
	draw(*smpInstance->mpBackbuffer, drawingX, drawingY, buffer, scale);
}

void GraphicsSystem::draw(const GraphicsBuffer& targetBuffer, const float& drawingX, const float& drawingY, const GraphicsBuffer& buffer, const float& scale)
{
	const int& BUFFER_WIDTH = buffer.getWidth();
	const int& BUFFER_HEIGHT = buffer.getHeight();
	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, targetBuffer.mpBitmapTexture);

	SDL_Rect gdSprite;

	gdSprite.x = static_cast<int>(std::round(drawingX));
	gdSprite.y = static_cast<int>(std::round(drawingY));
	gdSprite.w = BUFFER_WIDTH;
	gdSprite.h = BUFFER_HEIGHT;

	SDL_RenderCopy(smpInstance->mpRenderer, buffer.mpBitmapTexture, nullptr, &gdSprite);

	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
}

void GraphicsSystem::draw(const float& drawingX, const float& drawingY, GraphicsBuffer& imageBuffer, const float& scale)
{
	draw(*smpInstance->mpBackbuffer, drawingX, drawingY, imageBuffer, scale);
}

void GraphicsSystem::draw(const GraphicsBuffer& targetBuffer, const float& drawingX, const float& drawingY, GraphicsBuffer& imageBuffer, const float& scale)
{
	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, targetBuffer.mpBitmapTexture);

	//SDL_Texture* textureText = SDL_CreateTextureFromSurface(smpInstance->mpRenderer, &surface);

	SDL_Rect gdSprite;

	gdSprite.x = static_cast<int>(std::round(drawingX));
	gdSprite.y = static_cast<int>(std::round(drawingY));
	gdSprite.w = imageBuffer.getWidth();
	gdSprite.h = imageBuffer.getHeight();

	SDL_RenderCopy(smpInstance->mpRenderer, imageBuffer.mpBitmapTexture, nullptr, &gdSprite);
	
	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
	//SDL_DestroyTexture(textureText);
}

void GraphicsSystem::drawCentered(const GraphicsBuffer& buffer, const float& scale)
{
	float centerX = (getDisplayWidth() - buffer.getWidth() * scale) / 2.0f;
	float centerY = (getDisplayHeight() - buffer.getHeight() * scale) / 2.0f;

	draw(centerX, centerY, buffer, scale);
}

void GraphicsSystem::drawRotated(const int& bitmapStartX, const int& bitmapStartY, const int& width, const int& height, const float& drawingX, const float& drawingY, const GraphicsBuffer& buffer, const float& degrees, const float& scale)
{
	const int& BUFFER_WIDTH = buffer.getWidth();
	const int& BUFFER_HEIGHT = buffer.getHeight();
	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, smpInstance->mpBackbuffer->mpBitmapTexture);

	SDL_Point* center = new SDL_Point(SDL_Point{ (width / 2), (height / 2) });
	SDL_Rect gdSprite;

	gdSprite.x = static_cast<int>(std::round(drawingX));
	gdSprite.y = static_cast<int>(std::round(drawingY));
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

	delete center;
}

void GraphicsSystem::drawScaledToFit(const float& drawingX, const float& drawingY, const GraphicsBuffer& buffer, const int& width, const int& height)
{
	float xScale = width / static_cast<float>(buffer.getWidth());
	float yScale = height / static_cast<float>(buffer.getHeight());

	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, smpInstance->mpBackbuffer->mpBitmapTexture);

	SDL_Rect gdSprite;

	gdSprite.x = static_cast<int>(std::round(drawingX));
	gdSprite.y = static_cast<int>(std::round(drawingY));
	gdSprite.w = static_cast<int>(width * xScale);
	gdSprite.h = static_cast<int>(height * yScale);

	SDL_RenderCopy(smpInstance->mpRenderer, buffer.mpBitmapTexture, nullptr, &gdSprite);

	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
}

void GraphicsSystem::draw(const float& drawingX, const float& drawingY, const Sprite& sprite, const float& scale)
{
	draw(*smpInstance->mpBackbuffer, drawingX, drawingY, sprite, scale);
}

void GraphicsSystem::draw(const GraphicsBuffer& targetBuffer, const float& drawingX, const float& drawingY, const Sprite& sprite, const float& scale)
{
	draw(targetBuffer, drawingX, drawingY, sprite.mSPRITE_BUFFER);
}

void GraphicsSystem::drawCentered(const Sprite& sprite, const float& scale)
{
	float centerX = std::round((getDisplayWidth() - sprite.getWidth() * scale) / 2.0f);
	float centerY = std::round((getDisplayHeight() - sprite.getHeight() * scale) / 2.0f);

	draw(centerX, centerY, sprite, scale);
}

void GraphicsSystem::writeText(const float& startingX, const float& startingY, const Font& font, const Color& color, const std::string& text)
{
	writeText(*smpInstance->mpBackbuffer, startingX, startingY, font, color, text);
}

void GraphicsSystem::writeTextCenteredVertically(const float& startingX, const Font& font, const Color& color, const std::string& text)
{
	Vector2D centeredPos = getCenteredTextPosition(font, text);
	writeText(std::round(startingX), std::round(centeredPos.getY()), font, color, text);
}

void GraphicsSystem::writeTextCenteredHorizontally(const float& startingY, const Font& font, const Color& color, const std::string& text)
{
	Vector2D centeredPos = getCenteredTextPosition(font, text);
	writeText(std::round(centeredPos.getX()), std::round(startingY), font, color, text);
}

void GraphicsSystem::writeTextCentered(const Font& font, const Color& color, const std::string& text)
{
	Vector2D centeredPos = getCenteredTextPosition(font, text);
	writeText(std::round(centeredPos.getX()), std::round(centeredPos.getY()), font, color, text);
}

void GraphicsSystem::writeText(const GraphicsBuffer& targetBuffer, const float& startingX, const float& startingY, const Font& font, 
	const Color& color, const std::string& text)
{
	SDL_Texture* pPreviousBitmap = SDL_GetRenderTarget(smpInstance->mpRenderer);

	SDL_SetRenderTarget(smpInstance->mpRenderer, smpInstance->mpBackbuffer->mpBitmapTexture);

	SDL_Surface* surfaceText = TTF_RenderText_Blended(font.mpFont, text.c_str(), toSDLColor(color));
	
	SDL_Rect gdSprite;
	Vector2D fontDimensions = Font::getDimensions(font, text);

	gdSprite.x = static_cast<int>(std::round(startingX));
	gdSprite.y = static_cast<int>(std::round(startingY));
	gdSprite.w = static_cast<int>(std::round(fontDimensions.getX()));
	gdSprite.h = static_cast<int>(std::round(fontDimensions.getY()));

	SDL_Texture* textureText = SDL_CreateTextureFromSurface(smpInstance->mpRenderer, surfaceText);

	SDL_RenderCopy(smpInstance->mpRenderer, textureText, nullptr, &gdSprite);

	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);


	//draw(startingX, startingY, surfaceText);

	SDL_SetRenderTarget(smpInstance->mpRenderer, pPreviousBitmap);
	SDL_FreeSurface(surfaceText);
	SDL_DestroyTexture(textureText);
}

Vector2D GraphicsSystem::getCenteredTextPosition(const Font& font, const std::string& text)
{
	Vector2D centeredDimensions = Font::getDimensions(font, text);
	float startingX = ((float)GraphicsSystem::getDisplayWidth() - centeredDimensions.getX()) / 2.0f;
	float startingY = ((float)GraphicsSystem::getDisplayHeight() - centeredDimensions.getY()) / 2.0f;
	centeredDimensions.setX(startingX);
	centeredDimensions.setY(startingY);
	return centeredDimensions;
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