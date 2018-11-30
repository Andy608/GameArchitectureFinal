/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef SPRITE_H_
#define SPRITE_H_

#include <Trackable.h>

class GraphicsBuffer;

class Sprite : public Trackable
{
public:
	const GraphicsBuffer& mSPRITE_BUFFER;
	
	Sprite(const GraphicsBuffer& spriteBuffer);
	Sprite(const GraphicsBuffer& spriteBuffer, const int startingX, const int startingY, const int width, const int height);
	~Sprite();

	const int& getStartingX() const;
	const int& getStartingY() const;
	const int& getWidth() const;
	const int& getHeight() const;

private:
	const int mSTARTING_X;
	const int mSTARTING_Y;
	const int mWIDTH;
	const int mHEIGHT;
};

#endif