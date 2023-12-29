#include "customdish.h"

CustomDish::CustomDish() {}

CustomDish::CustomDish(const string &name, int caloricContent, double proteinContent,
                       double fatContent, double carbohydrateContent,
                       const string &description, const vector<pair<string, double>> &recipe)
    : FoodItem(name, caloricContent, proteinContent, fatContent, carbohydrateContent),
    description(description),
    recipe(recipe){

}

void CustomDish::setDescription(const string &desc){
    description = desc;
}


void CustomDish::addIngredient(const string &ingredient, double quantity){
    recipe.push_back(make_pair(ingredient, quantity));
}


vector<pair<string, double>> CustomDish::getRecipe() const{
    return recipe;
}

void CustomDish::setFoodName(const std::string &foodName) {
    this->foodName = foodName;
}

string CustomDish::getDescription() const{
    return description;
}
