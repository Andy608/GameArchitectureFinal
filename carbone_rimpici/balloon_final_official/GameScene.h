/*
* Author:		Andrew Rimpici, Tim Carbone
* Date:			5/4/2018
* Class:		Game Architecture <EGP310-03>
* Assignment:	Final Project
* Certification of Authenticity: I certify that this assignment is entirely our own work.
*/

#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "Scene.h"

class Player;
class Score;
class WallManager;

class GameScene : public Scene
{
public:
	friend class SceneManager;

	void start();
	void end();

	void cleanup();

	void update(float deltaTime);
	void draw();
	void save();
	void load();

	void checkCollision();


private:
	Player* mpPlayer;
	Score* mpScore;
	WallManager* mpWallManager;

	void setupNewGame();
	void difficultyCheck();
	void endGame();

	inline GameScene() : Scene(EnumScene::GAME_SCENE) {};
	inline ~GameScene() { cleanup(); };
};

#endif