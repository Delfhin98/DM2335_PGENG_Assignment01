#pragma once

#include "cocos2d.h"

class TouchScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual bool onTouch_Began(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouch_Ended(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouch_Moved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouch_Cancelled(cocos2d::Touch*, cocos2d::Event*);
	CREATE_FUNC(TouchScene);

private:
	cocos2d::Label* labelTouchInfo;
};