#pragma once
#ifndef _RECIPE_DATABASE_H_
#define _RECIPE_DATABASE_H_
#include "Recipes.h"

class RecipeDatabase
{
private:
	~RecipeDatabase();
	//static RecipeDatabase* RD_Instance;

public:
	RecipeDatabase();
	vector<Recipe*> list_recipes;
	int iRecNum;
	/*static RecipeDatabase* GetInstance() {
		if (RD_Instance == NULL)
		{
			RD_Instance = new RecipeDatabase();
		}
		return RD_Instance;
	};*/
};

#endif // _RECIPE_DATABASE_H_
