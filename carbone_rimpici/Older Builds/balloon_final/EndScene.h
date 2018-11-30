#ifndef END_SCENE_H_
#define END_SCENE_H_

#include "Scene.h"
#include <vector>
#include "UITextButton.h"
#include <EventListener.h>

class EndScene : public Scene
{
public:
	friend class SceneManager;

	virtual ~EndScene();

	virtual void start();
	virtual void end();

	virtual void cleanup();

	virtual void update(float deltaTime);
	virtual void draw();
	virtual void save();
	virtual void load();

private:
	std::vector<UITextButton*> mMenuButtons;

	EndScene();
};

#endif