#include "Recipe_Database.h"

RecipeDatabase* RecipeDatabase::RD_Instance = NULL;

RecipeDatabase::RecipeDatabase()
{
	ifstream file_recipes;
	string temp;
	istringstream ss(temp);
	Recipe* tempRecipe = new Recipe();
	iRecNum = 0;
	int iElement = 1;
	file_recipes.open("../Classes/Recipes/recipes.txt");

	while (file_recipes.is_open() && !file_recipes.eof())
	{
		for (iElement; iElement <= 9; ++iElement)
		{
			if (iElement == 9)
			{
				getline(file_recipes, temp, '\n');
			}
			else
			{
				getline(file_recipes, temp, ',');
			}
			tempRecipe->SetData(temp, iElement);
		}
		list_recipes.push_back(tempRecipe);
		tempRecipe = new Recipe();
		iElement = 1;
		++iRecNum;
	}
	file_recipes.close();
}

RecipeDatabase::~RecipeDatabase()
{
}
