#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include "Scene.h"

class Player;
class Score;
class CeilingFloorManager;

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
	CeilingFloorManager* mpCFManager;

	void difficultyCheck();
	void endGame();

	inline GameScene() : Scene(EnumScene::GAME_SCENE) {};
	inline ~GameScene() { cleanup(); };
};

#endif