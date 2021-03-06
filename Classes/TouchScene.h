#pragma once

#include "cocos2d.h"

class TouchScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// Update Every Frame
	virtual void update(float);

	

	virtual bool onTouch_Began(cocos2d::Touch*, cocos2d::Event*);
	virtual bool onTouch_Ended(cocos2d::Touch*, cocos2d::Event*);
	virtual bool onTouch_Moved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouch_Cancelled(cocos2d::Touch*, cocos2d::Event*);
	CREATE_FUNC(TouchScene);
	
private:
	cocos2d::Label* labelTouchInfo;
	cocos2d::Label* labelTouchInfo1;
	cocos2d::Label* labelTouchInfo2;
	cocos2d::Vec2* start1;
	cocos2d::Vec2* end1;
	cocos2d::DrawNode* draw;
	cocos2d::DrawNode* draw1;
	cocos2d::Vec2* start;
	cocos2d::Vec2* end;
};