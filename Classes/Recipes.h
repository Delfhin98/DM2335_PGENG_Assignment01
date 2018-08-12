#pragma once
#ifndef _RECIPES_H_
#define _RECIPES_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

enum COOKING_TYPE
{
	CT_WATER = 0,
	CT_OIL,
	CT_OVEN,
	CT_NONE
};
enum INGREDIENT_TYPE
{
	ING_EGG = 0,
	ING_POTATO,
	ING_FISH,
	ING_CHICKEN,
	ING_SPINACH,
	ING_CARROT,
	ING_TOMATO,
	ING_BUTTER,
	ING_SALT,
	ING_PEPPER,
	ING_FRIES,
	ING_FISHFILLET,
	ING_ROASTEDCHICKEN,
	ING_NONE
};

class Recipe
{
public:
	Recipe();
	~Recipe();

	string GetRecipeName();
	void SetData(string val, int element);
	void SetMethod();
	string GetMethod();
private:
	string recipe_name;
	INGREDIENT_TYPE main_ingredient;
	INGREDIENT_TYPE sub_ingredient1;
	INGREDIENT_TYPE sub_ingredient2;
	INGREDIENT_TYPE sub_ingredient3;
	string recipe_filename;
	string recipe_method;
	COOKING_TYPE COOKTYPE;
	

	void SetCookingType(int val);
	void SetIngredientType(int counter, int val);
};

#endif // _MAINMENU_SCENE_H_
