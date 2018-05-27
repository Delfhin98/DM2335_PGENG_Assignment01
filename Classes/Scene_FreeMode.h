#ifndef _SCENE_FREE_MODE_H_
#define _SCENE_FREE_MODE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
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
    CREATE_FUNC(GameScene);
};

#endif // _MAINMENU_SCENE_H_
