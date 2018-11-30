/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "Color.h"

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
	red(r),
	green(g),
	blue(b),
	alpha(a)
{

}

Color::Color(unsigned char r, unsigned char g, unsigned char b) :
	Color(r, g, b, 255)
{

}
