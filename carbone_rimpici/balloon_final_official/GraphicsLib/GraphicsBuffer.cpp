/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <iostream>
#include "GraphicsBuffer.h"
#include "Color.h"
#include "GraphicsSystem.h"
#include <SDL.h>
#include <SDL_image.h>

GraphicsBuffer::GraphicsBuffer(SDL_Surface* pBitmapSurface) :
	mpBitmapSurface(pBitmapSurface),
	mpBitmapTexture(surfaceToTexture(pBitmapSurface)),
	mOwnsBitmap(false)
{
	
}

/*GraphicsBuffer::GraphicsBuffer(int width, int height, Color defaultColor) :
	mpBitmap(SDL_CreateRGBSurfaceFrom(width, height)),
	mBitmapWidth(width),
	mBitmapHeight(height),
	mOwnsBitmap(true)
{
	ALLEGRO_BITMAP* previousBuffer = al_get_target_bitmap();
	al_set_target_bitmap(mpBitmap);
	al_clear_to_color(GraphicsSystem::toAllegroColor(defaultColor));
	al_set_target_bitmap(previousBuffer);
}*/

GraphicsBuffer::GraphicsBuffer(const std::string& imagePath) :
	mpBitmapSurface(loadSurface(imagePath)),
	mpBitmapTexture(surfaceToTexture(mpBitmapSurface)),
	mOwnsBitmap(true)
{

}

GraphicsBuffer::~GraphicsBuffer()
{
	if (mOwnsBitmap)
	{
		SDL_DestroyTexture(mpBitmapTexture);
		mpBitmapTexture = nullptr;

		SDL_FreeSurface(mpBitmapSurface);
		mpBitmapSurface = nullptr;
	}
}

const int& GraphicsBuffer::getWidth() const
{
	return mBitmapWidth;
}

const int& GraphicsBuffer::getHeight() const
{
	return mBitmapHeight;
}

SDL_Surface* GraphicsBuffer::loadSurface(const std::string& imagePath)
{
	SDL_Surface* pSurface = IMG_Load(imagePath.c_str());

	if (!pSurface)
	{
		std::cout << "Error loading surface: \'" << imagePath.c_str() << "\'. Error: " << IMG_GetError() << std::endl;
	}

	return pSurface;
}

SDL_Texture* GraphicsBuffer::surfaceToTexture(SDL_Surface* pSurface)
{
	SDL_Texture* pTexture = nullptr;

	pTexture = SDL_CreateTextureFromSurface(GraphicsSystem::getInstance()->getRenderer(), pSurface);

	if (!pTexture)
	{
		std::cout << "Error converting surface to texture. SDL Error: " << SDL_GetError() << std::endl;
	}

	mBitmapWidth = pSurface->w;
	mBitmapHeight = pSurface->h;

	return pTexture;
}