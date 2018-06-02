#pragma once
#ifndef _RECIPES_H_
#define _RECIPES_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::to_string;

enum COOKING_TYPE
{
	CT_NONE = 0,
	CT_WATER,
	CT_LOW_OIL,
	CT_HIGH_OIL,
	CT_OVEN
};
enum SEASONING_TYPE
{
	ST_NONE = 0,
	ST_SALT,
	ST_PEPPER
};

class Recipe
{
public:
	Recipe();
	~Recipe();

	void GetRecipe(const string name);

private:
	string recipe_name;
	string main_ingredient;
	string sub_ingredient1;
	string sub_ingredient2;
	string sub_ingredient3;
	vector<string> recipe_method;

	void SetRecipe();
};

#endif // _MAINMENU_SCENE_H_
