#ifndef _TESTING_SCENE_H_
#define _TESTING_SCENE_H_

#include "cocos2d.h"
#include "CookingAnimation.h"
using namespace cocos2d;

class Testing : public cocos2d::Scene
{
	CookingAnimation* cookingAnim;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeScene(float time, cocos2d::Scene *scene);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);

	// Update Every Frame
	virtual void update(float);

	// implement the "static create()" method manually
	CREATE_FUNC(Testing);
};

#endif // _Testing_SCENE_H_
