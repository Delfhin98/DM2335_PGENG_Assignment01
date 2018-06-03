#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character.h"

class HelloWorld : public cocos2d::Scene
{
	GameChar * bluething;
	
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	virtual void onMouseDown(Event*);
	virtual void update(float);
	
	GameChar* getChar() { return bluething; };
	
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
