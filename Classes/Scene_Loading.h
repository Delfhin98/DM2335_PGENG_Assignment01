#pragma once
#ifndef _SCENE_LOADING_H_
#define _SCENE_LOADING_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>

using namespace cocos2d;
using std::string;
using std::vector;

class LoadingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeScene(float time, cocos2d::Scene *scene);
	void loadingTextureFinished(Texture2D* texture);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);

	// Update Every Frame
	virtual void update(float);
	//static LoadingScene* LS_Instance;
	vector<string> Resources;
	int currResource;
	int numOfResource;
	int percentage;
	Label* textLabel;
	bool hasFinished;
	// implement the "static create()" method manually
	CREATE_FUNC(LoadingScene);
};

#endif