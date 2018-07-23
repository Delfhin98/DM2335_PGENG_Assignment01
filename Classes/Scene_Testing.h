#ifndef _SCENE_TESTING_H
#define _SCENE_TESTING_H

#include "cocos2d.h"
using namespace cocos2d;

class SceneTesting : public cocos2d::Scene
{
	std::vector <std::pair<std::pair<const char*, const char*>, Sprite*>> objectContainer;

	Sprite* popUp;
	bool isPopUpOpen;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeScene(float time, cocos2d::Scene *scene);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);

	// Touch
	bool onTestTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTestTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTestTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// Update Every Frame
	virtual void update(float);

	// Common Pop Up Menu
	void openPopUpMenu(const char* objectID);
	void closePopUpMenu();

	// implement the "static create()" method manually
	CREATE_FUNC(SceneTesting);
};

#endif // _MAINMENU_SCENE_H_
