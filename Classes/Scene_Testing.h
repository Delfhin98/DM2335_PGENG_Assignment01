#ifndef _SCENE_TESTING_H_
#define _SCENE_TESTING_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CookingAnimation.h"

using namespace cocos2d;

class TestingScene : public cocos2d::Scene
{
	CookingAnimation* cookingAnim;
	Sprite* spicesPopUpMenu;
	bool isSpicesPopUpMenu;
	std::vector <std::pair<std::pair<const char*, const char*>, Sprite*>> objectContainer;
	std::vector<const char*, std::pair<const char*, const char*>> spicesInformation;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeScene(float time, cocos2d::Scene *scene);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);

	// Touch
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	// Update Every Frame
	virtual void update(float);

	// Spices
	void openPopUpMenu(const char* objectID);
	void closePopUpMenu();

    // implement the "static create()" method manually
    CREATE_FUNC(TestingScene);
};

#endif // _SCENE_TESTING_H_
