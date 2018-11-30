/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef FONT_H_
#define FONT_H_

#include <Trackable.h>
#include <SDL_ttf.h>

class Font : public Trackable
{
	friend class GraphicsSystem;

public:
	Font(const std::string& fontPath, int fontSize);
	~Font();

	const int& getSize() const;
	TTF_Font* getFont() const;

private:
	int mSize;
	TTF_Font* mpFont;

	TTF_Font* initFont(const std::string& fontPath, int fontSize);
};

#endif