/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			3/30/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include "System.h"
#include "GraphicsSystem.h"

#include <iostream>
#include <assert.h>

System* System::smpInstance = nullptr;

System* System::getInstance()
{
	assert(smpInstance);
	return smpInstance;
}

bool System::initInstance(const int& displayWidth, const int& displayHeight)
{
	if (!smpInstance)
	{
		std::cout << "System instance is null, creating new instance." << std::endl;
		smpInstance = new System();
	}

	return smpInstance->init(displayWidth, displayHeight);
}

void System::cleanupInstance()
{
	if (smpInstance)
	{
		delete smpInstance;
		smpInstance = nullptr;
	}
}

System::System() :
	mpInputSystem (nullptr),
	mIsInitialized (false)
{

}

System::~System()
{
	cleanup();
}

bool System::init(const int& displayWidth, const int& displayHeight)
{
	if (!mIsInitialized)
	{
		mIsInitialized = true;

		if (!GraphicsSystem::initInstance(displayWidth, displayHeight))
		{
			std::cout << "Error initializing Graphics System." << std::endl;
			cleanup();
		}

		mpInputSystem = new InputSystem();

		if (!mpInputSystem->init())
		{
			std::cout << "Error initializing Input System." << std::endl;
			cleanup();
		}
	}

	return mIsInitialized;
}

void System::cleanup()
{
	if (mIsInitialized)
	{
		GraphicsSystem::cleanupInstance();
		
		delete mpInputSystem;
		mpInputSystem = nullptr;

		mIsInitialized = false;
	}
}

InputSystem* System::getInputSystem() const
{
	return mpInputSystem;
}