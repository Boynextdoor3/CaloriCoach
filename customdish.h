#ifndef CUSTOMDISH_H
#define CUSTOMDISH_H

#include "fooditem.h"

class CustomDish : public FoodItem
{
    string description;
    vector<pair<string, double>> recipe;

public:
    CustomDish();
    CustomDish(const string &name, int caloricContent, double proteinContent,
               double fatContent, double carbohydrateContent,
               const string &description, const vector<pair<string, double>> &recipe);

    string getDescription() const;
    void setDescription(const string &desc);
    void setFoodName(const std::string &foodName);
    void addIngredient(const string &ingredient, double quantity);
    vector<pair<string, double>> getRecipe() const;

};

#endif // CUSTOMDISH_H
