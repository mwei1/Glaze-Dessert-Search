//
// Created by lawre on 3/2/2026.
//
#include <iostream>
#include "CSVReader.h"
#include <vector>



int main() {
    std::vector<Recipe> recipes = CSVReader::loadRecipesFromFile("resources/RecipeData.csv");
    std::cout << recipes.size() << "\n\n";
    for (int i=0;i<5;i++) {
        std::cout << recipes[i].name << " " << recipes[i].prepTime << " " << recipes[i].difficulty << " " << recipes[i].mainIngredient << "\n";
    }
    return 0;
}

