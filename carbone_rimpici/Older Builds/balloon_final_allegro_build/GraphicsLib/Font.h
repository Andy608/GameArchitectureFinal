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

struct ALLEGRO_FONT;

class Font : public Trackable
{
	friend class GraphicsSystem;

public:
	Font(const std::string& fontPath, int fontSize);
	~Font();

	const int& getSize() const;

private:
	int mSize;
	ALLEGRO_FONT* mpFont;

	ALLEGRO_FONT* initFont(const std::string& fontPath, int fontSize);
};

#endif