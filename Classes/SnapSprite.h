#pragma once

#include "cocos2d.h"

class OHsnap : public cocos2d::Layer
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
	//void modifySpriteposition(cocos2d::Touch*,cocos2d::Event*);
	CREATE_FUNC(OHsnap);

	//Sprite sprite1; //create("strawberry.png");
private:
	bool onsprite;
};