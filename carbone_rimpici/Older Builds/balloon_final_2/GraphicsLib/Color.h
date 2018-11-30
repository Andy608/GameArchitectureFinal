/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef COLOR_H_
#define COLOR_H_

#include <Trackable.h>

struct Color : public Trackable
{
	friend class GraphicsSystem;
	friend class GraphicsBuffer;

	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	Color(unsigned char r, unsigned char g, unsigned char b);

	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;

	bool operator==(const Color& another)
	{
		return (red == another.red && green == another.green && blue == another.blue && alpha == another.alpha);
	}
};

#endif