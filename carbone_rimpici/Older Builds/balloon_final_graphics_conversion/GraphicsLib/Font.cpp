/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <SDL.h>

//#include <allegro5/allegro_ttf.h>
#include "Font.h"

Font::Font(const std::string& fontPath, int fontSize) :
	mSize(fontSize),
	mpFont(initFont(fontPath, fontSize))
{
	
}

Font::~Font()
{
	TTF_CloseFont(mpFont);
}

const int& Font::getSize() const
{
	return mSize;
}

TTF_Font* Font::getFont() const
{
	return mpFont;
}

TTF_Font* Font::initFont(const std::string& fontPath, int fontSize)
{
	TTF_Font* pfont = TTF_OpenFont(fontPath.c_str(), fontSize);

	if (pfont == nullptr)
	{
		std::cout << "Error initializing font. Font path: " << fontPath.c_str() << std::endl;
	}

	return pfont;
}