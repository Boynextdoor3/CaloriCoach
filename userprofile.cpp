

#include "userprofile.h"

UserProfile::UserProfile() {}

UserProfile::UserProfile(const std::string &name, double weight, double goal, const std::string &plan)
    : userName(name), userWeight(weight), userGoal(goal), userPlan(plan) {}

string UserProfile::getUserName() const {
    return userName;
}

double UserProfile::getUserWeight() const {
    return userWeight;
}

string UserProfile::getUserPlan() const {
    return userPlan;
}

double UserProfile::getUserGoal() const {
    return userGoal;
}

