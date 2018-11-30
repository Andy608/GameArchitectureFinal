/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <allegro5/display.h>
#include <allegro5/allegro_color.h>
#include <iostream>
#include "GraphicsBuffer.h"
#include "Color.h"
#include "GraphicsSystem.h"
#include <allegro5/bitmap.h>

GraphicsBuffer::GraphicsBuffer(ALLEGRO_BITMAP* pBitmap) :
	mpBitmap(pBitmap),
	mBitmapWidth(initWidth(pBitmap)),
	mBitmapHeight(initHeight(pBitmap)),
	mOwnsBitmap(false)
{
	
}

GraphicsBuffer::GraphicsBuffer(int width, int height, Color defaultColor) :
	mpBitmap(al_create_bitmap(width, height)),
	mBitmapWidth(width),
	mBitmapHeight(height),
	mOwnsBitmap(true)
{
	ALLEGRO_BITMAP* previousBuffer = al_get_target_bitmap();
	al_set_target_bitmap(mpBitmap);
	al_clear_to_color(GraphicsSystem::toAllegroColor(defaultColor));
	al_set_target_bitmap(previousBuffer);
}

GraphicsBuffer::GraphicsBuffer(const std::string& imagePath) :
	mpBitmap(loadBitmap(imagePath)),
	mBitmapWidth(initWidth(mpBitmap)),
	mBitmapHeight(initHeight(mpBitmap)),
	mOwnsBitmap(true)
{

}

GraphicsBuffer::~GraphicsBuffer()
{
	if (mOwnsBitmap)
	{
		al_destroy_bitmap(mpBitmap);
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

Color GraphicsBuffer::getPixelColor(int x, int y) const
{
	ALLEGRO_COLOR c = al_get_pixel(mpBitmap, x, y);
	return Color(c.r * 255.0f, c.g * 255.0f, c.b * 255.0f, c.a * 255.0f);
}

ALLEGRO_BITMAP* GraphicsBuffer::loadBitmap(const std::string& imagePath)
{
	ALLEGRO_BITMAP* pBitmap = al_load_bitmap(imagePath.c_str());

	if (pBitmap == nullptr)
	{
		std::cout << "Error loading image: \'" << imagePath.c_str() << "\'. No image found at that location." << std::endl;
	}
	
	return pBitmap;
}

int GraphicsBuffer::initWidth(ALLEGRO_BITMAP* pBitmap)
{
	if (pBitmap == nullptr)
	{
		std::cout << "Bitmap is null!";
		return 0;
	}
	else
	{
		return al_get_bitmap_width(mpBitmap);
	}
}

int GraphicsBuffer::initHeight(ALLEGRO_BITMAP* pBitmap)
{
	if (pBitmap == nullptr)
	{
		std::cout << "Bitmap is null!";
		return 0;
	}
	else
	{
		return al_get_bitmap_height(mpBitmap);
	}
}