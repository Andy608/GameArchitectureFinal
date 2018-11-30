/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#include <MemoryTracker.h>
#include <EventSystem.h>
#include "Game.h"

using namespace std;

int main()
{
	const int DISPLAY_WIDTH  = static_cast<int>(1920 / 1.5f);	//1280
	const int DISPLAY_HEIGHT = static_cast<int>(1080 / 1.5f);	//720

	EventSystem::initInstance();
	Game::initInstance();
	Game::getInstance()->init(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	Game::getInstance()->loop();

	Game::cleanupInstance();
	EventSystem::cleanupInstance();

	gMemoryTracker.reportAllocations(cout);

	system("pause");
	return 0;

}