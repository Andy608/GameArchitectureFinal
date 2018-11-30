#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <map>
#include <Trackable.h>
#include "Scene.h"

enum EnumScene;

class SceneManager : public Trackable
{
public:
	SceneManager();
	~SceneManager();

	bool initScenes();

	void update(float deltaTime);
	void draw();
	void save();

	void setCurrentScene(EnumScene scene);
	inline EnumScene getCurrentSceneType() const { return mpCurrentScene->getSceneType(); };

private:
	bool mIsInitialized = false;
	std::map<EnumScene, Scene*> mSceneList;
	Scene* mpCurrentScene = nullptr;
};

#endif