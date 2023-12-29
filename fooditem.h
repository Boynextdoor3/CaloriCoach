#ifndef FOODITEM_H
#define FOODITEM_H

#include <vector>
#include <utility>
#include <string>
#include <list>

using namespace std;

class FoodItem
{
protected:
    string foodName;
    int caloricContent;
    double proteinContent;
    double fatContent;
    double carbohydrateContent;

public:
    FoodItem();
    FoodItem(string foodName, int caloricContent, double proteinContent, double fatContent, double carbohydrateContent);

    string getfoodName() const;
    int getcaloricContent() const;
    double getproteinContent() const;
    double getfatContent() const;
    double getcarbohydrateContent() const;

    void setCaloricContent(int caloricContent);
    void setProteinContent(double proteinContent);
    void setFatContent(double fatContent);
    void setCarbohydrateContent(double carbohydrateContent);

    void calculateCaloricContent();



};

#endif // FOODITEM_H
