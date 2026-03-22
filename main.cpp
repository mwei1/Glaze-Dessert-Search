//
// Created by lawre on 3/2/2026.
//
#include <iostream>
#include "CSVReader.h"
#include <vector>
#include "Trie.h"
#include "HashTable.h"

int main() {
    std::vector<Recipe> recipes = CSVReader::loadRecipesFromFile("../resources/recipes.csv");
    std::cout << recipes.size() << "\n\n";

    Trie t;
    for (int i=0;i<recipes.size();i++) {
        t.insert(recipes[i].name, i);
    }
    std::cout << "\n\n";
    std::string testSearchName = "Balsamic Bombe";
    std::vector<int> testFoundIndex = t.search(testSearchName);
    if (!testFoundIndex.empty()) {
        for (int index : testFoundIndex) {
            std::cout << recipes[index].name << " " << recipes[index].prepTime << " " << recipes[index].difficulty << " " << recipes[index].mainIngredient << " " << recipes[index].allergens << "\n";
        }
    }else {
        std::cout << "Recipe not found.";
    }

    std::string testPrefix = "Bal";
    std::vector<int> testFoundPrefix = t.searchByPrefix(testPrefix);
    if (!testFoundPrefix.empty()) {
        for (int index : testFoundPrefix) {
            std::cout << recipes[index].name << " " << recipes[index].prepTime << " " << recipes[index].difficulty << " " << recipes[index].mainIngredient << " " << recipes[index].allergens << "\n";
        }
    }else {
        std::cout << "No recipes found associated with that index.";
    }

    HashTable ht;
    for (int i = 0; i < recipes.size(); i++) {
        ht.insert(recipes[i].name, i);
    }
    std::vector<int> index = ht.search(testSearchName);
    if (!index.empty()) {
        for (int i : index) {
            std::cout << recipes[i].name <<  " " << std::endl;
        }
    }
    else {
        std::cout << testSearchName<< " not found." << std::endl;
    }

    std::cout << ht.getSize() << "\n\n";

    std::string testSearch = "Balsamic Bombe";
    std::vector<int> testFound = t.search(testSearchName);

    return 0;
}

