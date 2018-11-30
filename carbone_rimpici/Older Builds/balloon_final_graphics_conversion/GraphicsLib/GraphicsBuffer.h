/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef GRAPHICS_BUFFER_H_
#define GRAPHICS_BUFFER_H_

#include <Trackable.h>

struct SDL_Surface;
struct SDL_Texture;
struct Color;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;

public:
	//GraphicsBuffer(int width, int height, Color defaultColor);
	GraphicsBuffer(const std::string& imagePath);
	~GraphicsBuffer();

	const int& getWidth() const;
	const int& getHeight() const;

private:
	GraphicsBuffer(SDL_Surface* pBitmapSurface);
	SDL_Surface* mpBitmapSurface;
	SDL_Texture* mpBitmapTexture;
	int mBitmapWidth;
	int mBitmapHeight;
	bool mOwnsBitmap;

	SDL_Surface* loadSurface(const std::string& imagePath);
	SDL_Texture* surfaceToTexture(SDL_Surface* pSurface);
};

#endif