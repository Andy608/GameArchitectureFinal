/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "SpriteSheet.h"
#include "Sprite.h"
#include "GraphicsBuffer.h"

SpriteSheet::SpriteSheet(const GraphicsBuffer& spriteSheetBuffer, unsigned int rows, unsigned int columns, unsigned int spriteWidths, unsigned int spriteHeights) :
	mSPRITESHEET_BUFFER(spriteSheetBuffer),
	mROWS(rows),
	mCOLUMNS(columns),
	mSPRITE_WIDTHS(spriteWidths),
	mSPRITE_HEIGHTS(spriteHeights)
{
	unsigned int row;
	unsigned int column;
	for (row = 0; row < rows; ++row)
	{
		for (column = 0; column < columns; ++column)
		{
			mSprites.push_back(new Sprite(mSPRITESHEET_BUFFER, column * mSPRITE_WIDTHS, row * mSPRITE_HEIGHTS, mSPRITE_WIDTHS, mSPRITE_HEIGHTS));
		}
	}
}

SpriteSheet::SpriteSheet(const GraphicsBuffer& spriteSheetBuffer, unsigned int rows, unsigned int columns) :
	SpriteSheet(spriteSheetBuffer, rows, columns, static_cast<int>(spriteSheetBuffer.getWidth() / columns), static_cast<int>(spriteSheetBuffer.getHeight() / rows))
{

}

SpriteSheet::~SpriteSheet()
{
	unsigned int i;
	for (i = 0; i < mSprites.size(); ++i)
	{
		delete mSprites.at(i);
	}

	mSprites.clear();
}

const std::vector<Sprite*>& SpriteSheet::getSprites() const
{
	return mSprites;
}