#pragma once
#ifndef _RECIPES_H_
#define _RECIPES_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>

using namespace std;

enum COOKING_TYPE
{
	CT_NONE = 0,
	CT_WATER,
	CT_LOW_OIL,
	CT_HIGH_OIL,
	CT_OVEN
};

class Recipe
{
public:
	Recipe();
	~Recipe();

	string GetRecipeName();
	void SetData(string val, int element);
private:
	string recipe_name;
	string main_ingredient;
	string sub_ingredient1;
	string sub_ingredient2;
	string sub_ingredient3;
	string sub_ingredient4;
	string sub_ingredient5;
	string sub_ingredient6;
	COOKING_TYPE COOKTYPE;
	vector<string> recipe_method;
	int steps;

	void SetCookingType(string val);
};

#endif // _MAINMENU_SCENE_H_
