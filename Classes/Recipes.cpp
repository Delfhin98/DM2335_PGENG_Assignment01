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
		SetCookingType(val);
		break;
	case 3:
		main_ingredient = val;
		break;
	case 4:
		sub_ingredient1 = val;
		break;
	case 5:
		sub_ingredient2 = val;
		break;
	case 6:
		sub_ingredient3 = val;
		break;
	case 7:
		sub_ingredient4 = val;
		break;
	case 8:
		sub_ingredient5 = val;
		break;
	case 9:
		sub_ingredient6 = val;
		break;
	case 10:
		recipe_method = val;
		break;
	}
}

void Recipe::SetCookingType(string val)
{
	if (val == "water")
	{
		COOKTYPE = CT_WATER;
	}
	else if (val == "lowoil")
	{
		COOKTYPE = CT_LOW_OIL;
	}
	else if (val == "highoil")
	{
		COOKTYPE = CT_HIGH_OIL;
	}
	else if (val == "oven")
	{
		COOKTYPE = CT_OVEN;
	}
	else
	{
		COOKTYPE = CT_NONE;
	}
}

void Recipe::SetMethod()
{
	string temp = recipe_method;
	ifstream file_method;
	istringstream ss(temp);

	file_method.open("../Classes/Recipes/" + temp + ".txt");
	recipe_method.clear();
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
