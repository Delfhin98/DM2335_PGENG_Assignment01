#pragma once
#ifndef _SCENE_RECIPES_H_
#define _SCENE_RECIPES_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Recipes.h"

using namespace cocos2d;

class RecipeScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void RecipeDatabaseChangeScene(float time, cocos2d::Scene *scene);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);

	// Update Every Frame
	virtual void update(float);
	vector<string> list_recipes;
	string selected_recipe;
	int numOfRecipes;
	

	
	// implement the "static create()" method manually
	CREATE_FUNC(RecipeScene);
};

#endif