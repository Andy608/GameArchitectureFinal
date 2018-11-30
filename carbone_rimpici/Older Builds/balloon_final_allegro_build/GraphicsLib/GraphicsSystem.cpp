/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <string>
#include <assert.h>

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
		if (!al_init())
		{
			std::cout << "There was an error initializing Allegro." << std::endl;
			return false;
		}
		
		if (!al_init_image_addon())
		{
			std::cout << "There was an error initializing the Allegro Image Addon." << std::endl;
			return false;
		}

		if (!al_init_font_addon())
		{
			std::cout << "There was an error initializing the Allegro Font Addon." << std::endl;
			return false;
		}

		if (!al_init_ttf_addon())
		{
			std::cout << "There was an error initializing the Allegro TTF Addon." << std::endl;
			return false;
		}

		if (!al_init_primitives_addon())
		{
			std::cout << "There was an error initializing the Allegro Primitives Addon." << std::endl;
			return false;
		}

		if (!al_install_audio())
		{
			std::cout << "There was an error initializing the Allegro Audio Addon." << std::endl;
			return false;
		}

		if (!al_init_acodec_addon())
		{
			std::cout << "There was an error initializing the Allegro Acodec Addon." << std::endl;
			return false;
		}

		mpDisplay = al_create_display(displayWidth, displayHeight);
		mpBackbuffer = new GraphicsBuffer(al_get_backbuffer(mpDisplay));
		mIsInitialized = true;
	}

	return mIsInitialized;
}

void GraphicsSystem::cleanup()
{
	if (mIsInitialized)
	{
		al_destroy_display(mpDisplay);
		mpDisplay = nullptr;
		delete mpBackbuffer;
		mIsInitialized = false;
	}
}

const int GraphicsSystem::getDisplayWidth()
{
	return al_get_display_width(smpInstance->mpDisplay);
}

const int GraphicsSystem::getDisplayHeight()
{
	return al_get_display_height(smpInstance->mpDisplay);
}

void GraphicsSystem::flip()
{
	al_flip_display();
}

void GraphicsSystem::draw(const int& startingX, const int& startingY, const GraphicsBuffer& buffer, const float& scale)
{
	draw(*smpInstance->mpBackbuffer, startingX, startingY, buffer, scale);
}

void GraphicsSystem::draw(const GraphicsBuffer& targetBuffer, const int& startingX, const int& startingY, const GraphicsBuffer& buffer, const float& scale)
{
	const int& BUFFER_WIDTH = buffer.getWidth();
	const int& BUFFER_HEIGHT = buffer.getHeight();
	ALLEGRO_BITMAP* pPreviousBitmap = al_get_target_bitmap();

	al_set_target_bitmap(targetBuffer.mpBitmap);

	al_draw_scaled_bitmap(buffer.mpBitmap, 0, 0,
		BUFFER_WIDTH, BUFFER_HEIGHT, startingX, startingY, BUFFER_WIDTH * scale, BUFFER_HEIGHT * scale, 0);

	al_set_target_bitmap(pPreviousBitmap);
}

void GraphicsSystem::drawCentered(const GraphicsBuffer& buffer, const float& scale)
{
	int centerX = (getDisplayWidth() - buffer.getWidth() * scale) / 2.0f;
	int centerY = (getDisplayHeight() - buffer.getHeight() * scale) / 2.0f;

	draw(centerX, centerY, buffer, scale);
}

void GraphicsSystem::drawRotated(const int& bitmapStartX, const int& bitmapStartY, const int& width, const int& height, const float& startingX, const float& startingY, const GraphicsBuffer& buffer, const float& degrees, const float& scale)
{
	const int& BUFFER_WIDTH = buffer.getWidth();
	const int& BUFFER_HEIGHT = buffer.getHeight();
	ALLEGRO_BITMAP* pPreviousBitmap = al_get_target_bitmap();

	al_set_target_bitmap(smpInstance->mpBackbuffer->mpBitmap);

	al_draw_tinted_scaled_rotated_bitmap_region(
		buffer.mpBitmap,
		bitmapStartX, bitmapStartY, width, height,      // source bitmap region
		al_map_rgb(255, 255, 255),						// color, just use white if you don't want a tint
		width / 2, height / 2,							// center of rotation/scaling
		startingX, startingY,							// destination
		scale, scale,									// scale
		degrees * 3.14159 / 180.0, 0);					// angle and flags

	al_set_target_bitmap(pPreviousBitmap);
}

void GraphicsSystem::drawScaledToFit(const int& startingX, const int& startingY, const GraphicsBuffer& buffer, const float& width, const float& height)
{
	float xScale = width / static_cast<float>(buffer.getWidth());
	float yScale = height / static_cast<float>(buffer.getHeight());

	ALLEGRO_BITMAP* pPreviousBitmap = al_get_target_bitmap();

	al_set_target_bitmap(smpInstance->mpBackbuffer->mpBitmap);

	al_draw_scaled_bitmap(buffer.mpBitmap, 0, 0, buffer.getWidth(), buffer.getHeight(), startingX, startingY,
		buffer.getWidth() * xScale, buffer.getHeight() * yScale, 0);

	al_set_target_bitmap(pPreviousBitmap);
}

void GraphicsSystem::draw(const int& startingX, const int& startingY, const Sprite& sprite, const float& scale)
{
	draw(*smpInstance->mpBackbuffer, startingX, startingY, sprite, scale);
}

void GraphicsSystem::draw(const GraphicsBuffer& targetBuffer, const int& startingX, const int& startingY, const Sprite& sprite, const float& scale)
{
	const int& SPRITE_WIDTH = sprite.getWidth();
	const int& SPRITE_HEIGHT = sprite.getHeight();
	ALLEGRO_BITMAP* pPreviousBitmap = al_get_target_bitmap();

	al_set_target_bitmap(targetBuffer.mpBitmap);

	al_draw_scaled_bitmap(sprite.mSPRITE_BUFFER.mpBitmap, sprite.getStartingX(), sprite.getStartingY(), 
		SPRITE_WIDTH, SPRITE_HEIGHT, startingX, startingY, SPRITE_WIDTH * scale, SPRITE_HEIGHT * scale, 0);

	al_set_target_bitmap(pPreviousBitmap);
}

void GraphicsSystem::drawCentered(const Sprite& sprite, const float& scale)
{
	int centerX = (getDisplayWidth() - sprite.getWidth() * scale) / 2.0f;
	int centerY = (getDisplayHeight() - sprite.getHeight() * scale) / 2.0f;

	draw(centerX, centerY, sprite, scale);
}

void GraphicsSystem::writeText(const int& startingX, const int& startingY, const Font& font, const Color& color, const std::string& text)
{
	writeText(*smpInstance->mpBackbuffer, startingX, startingY, font, color, text);
}

void GraphicsSystem::writeText(const GraphicsBuffer& targetBuffer, const int& startingX, const int& startingY, const Font& font, 
	const Color& color, const std::string& text)
{
	ALLEGRO_BITMAP* pPreviousBitmap = al_get_target_bitmap();

	al_set_target_bitmap(targetBuffer.mpBitmap);
	
	al_draw_text(font.mpFont, toAllegroColor(color), startingX, startingY, ALLEGRO_ALIGN_CENTER, text.c_str());
	
	al_set_target_bitmap(pPreviousBitmap);
}

void GraphicsSystem::saveBuffer(const GraphicsBuffer& bufferToSave, const std::string& fileName)
{
	al_save_bitmap(fileName.c_str(), bufferToSave.mpBitmap);
}

const GraphicsBuffer& GraphicsSystem::getBackBuffer()
{
	return *smpInstance->mpBackbuffer;
}

ALLEGRO_COLOR GraphicsSystem::toAllegroColor(const Color& color)
{
	return al_map_rgba(color.red, color.green, color.green, color.alpha);
}