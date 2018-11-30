#ifndef ANIMATED_OBJECT_H_
#define ANIMATED_OBJECT_H_

#include <map>
#include <string>
#include "GameObject.h"
#include "Animation.h"

class AnimatedObject : public GameObject
{
public:
	AnimatedObject(const Sprite& pIdleSprite);
	virtual ~AnimatedObject();

	void addAnimation(std::string state, Animation* pAnimation);

	virtual void update(float delta) = 0;
	virtual void draw() = 0;

private:
	//List of animations depending on state.
	std::map<std::string, Animation*> mAnimationList;
};

#endif