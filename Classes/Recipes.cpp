#include "Recipes.h"

Recipe::Recipe()
{
}

Recipe::~Recipe()
{
}

string Recipe::GetRecipeName()
{
	return recipe_name;
}

void Recipe::SetData(string val, int element)
{
	switch (element)
	{
	case 1:
		recipe_name = val;
		break;
	case 2:
		SetCookingType(stoi(val));
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		SetIngredientType(element, stoi(val));
		break;
	case 7:
		recipe_filename = val;
		break;
	}
}

void Recipe::SetCookingType(int val)
{
	switch (val)
	{
	case 0:
		COOKTYPE = CT_WATER;
		break;
	case 1:
		COOKTYPE = CT_OIL;
		break;
	case 2:
		COOKTYPE = CT_OVEN;
		break;
	case 3:
		COOKTYPE = CT_NONE;
		break;
	}
}

void Recipe::SetIngredientType(int counter, int val)
{
	INGREDIENT_TYPE temp = ING_NONE;
	switch (val)
	{
	case 0:
		temp = ING_EGG;
		break;
	case 1:
		temp = ING_POTATO;
		break;
	case 2:
		temp = ING_FISH;
		break;
	case 3:
		temp = ING_CHICKEN;
		break;
	case 4:
		temp = ING_SPINACH;
		break;
	case 5:
		temp = ING_CARROT;
		break;
	case 6:
		temp = ING_TOMATO;
		break;
	case 7:
		temp = ING_BUTTER;
		break;
	case 8:
		temp = ING_SALT;
		break;
	case 9:
		temp = ING_PEPPER;
		break;
	case 10:
		temp = ING_FRIES;
		break;
	case 11:
		temp = ING_FISHFILLET;
		break;
	case 12:
		temp = ING_ROASTEDCHICKEN;
		break;
	}
	switch (counter)
	{
	case 3:
		main_ingredient = temp;
		break;
	case 4:
		sub_ingredient1 = temp;
		break;
	case 5:
		sub_ingredient2 = temp;
		break;
	case 6:
		sub_ingredient3 = temp;
		break;
	}
}

void Recipe::SetMethod()
{
	recipe_method = "";
	string temp = recipe_filename;
	ifstream file_method;
	istringstream ss(temp);

	file_method.open(temp + ".txt");
	while (file_method.is_open() && !file_method.eof())
	{
		getline(file_method, temp);
		recipe_method.append(temp + "\n");
	}
	file_method.close();
}

string Recipe::GetMethod()
{
	return recipe_method;
}
