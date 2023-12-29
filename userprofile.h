#ifndef USERPROFILE_H
#define USERPROFILE_H

#include "fooditem.h"

class UserProfile
{
private:
    string userName;
    double userWeight;
    string userPlan;
    double userGoal;
public:
    UserProfile();
    UserProfile(const string &name, double weight, double goal, const string &plan);

    string getUserName() const;
    double getUserWeight() const;
    string getUserPlan() const;
    double getUserGoal() const;

};

#endif // USERPROFILE_H
