/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <allegro5/allegro_ttf.h>
#include "Font.h"

Font::Font(const std::string& fontPath, int fontSize) :
	mSize(fontSize),
	mpFont(initFont(fontPath, fontSize))
{
	
}

Font::~Font()
{
	al_destroy_font(mpFont);
}

const int& Font::getSize() const
{
	return mSize;
}

ALLEGRO_FONT* Font::initFont(const std::string& fontPath, int fontSize)
{
	ALLEGRO_FONT* pfont = al_load_ttf_font(fontPath.c_str(), fontSize, 0);

	if (pfont == nullptr)
	{
		std::cout << "Error initializing font. Font path: " << fontPath.c_str() << std::endl;
	}

	return pfont;
}