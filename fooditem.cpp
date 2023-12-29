#include "fooditem.h"

FoodItem::FoodItem() {}

FoodItem::FoodItem(string foodName, int caloricContent, double proteinContent, double fatContent, double carbohydrateContent)
    : foodName(foodName), caloricContent(caloricContent), proteinContent(proteinContent), fatContent(fatContent), carbohydrateContent(carbohydrateContent) {
}

string FoodItem::getfoodName() const{
    return foodName;
}

int FoodItem::getcaloricContent() const{
    return caloricContent;
}

double FoodItem::getproteinContent() const{
    return proteinContent;
}

double FoodItem::getfatContent() const{
    return fatContent;
}

double FoodItem::getcarbohydrateContent() const{
    return carbohydrateContent;
}

void FoodItem::setCaloricContent(int caloricContent) {
    this->caloricContent = caloricContent;
}

void FoodItem::calculateCaloricContent() {
    caloricContent = proteinContent * 4 + fatContent * 9 + carbohydrateContent * 4;
}


void FoodItem::setProteinContent(double proteinContent) {
    this->proteinContent = proteinContent;
}

void FoodItem::setFatContent(double fatContent) {
    this->fatContent = fatContent;
}

void FoodItem::setCarbohydrateContent(double carbohydrateContent) {
    this->carbohydrateContent = carbohydrateContent;
}


