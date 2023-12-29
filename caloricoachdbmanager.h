#ifndef CALORICOACHDBMANAGER_H
#define CALORICOACHDBMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>
#include "userprofile.h"
#include "fooditem.h"
#include "customdish.h"

class CaloriCoachDBManager
{
    QSqlDatabase CaloriCoach_DB;
public:
    CaloriCoachDBManager();

    void connectToDatabase(const QString &host, const QString &dbName, const QString &user, int port);
    void createTables();
    void insertUserProfile(const UserProfile &userProfile);
    void insertFoodItem(const FoodItem &foodItem);
    FoodItem *searchProductByName(const QString &productName);
    void insertCustomDish(const CustomDish &customDish);
    bool updateUserProfile(const QString& userName, double userWeight, double userGoal, const QString& userPlan);
    CustomDish *searchCustomDishByName(const QString& dishName);

};

#endif // CALORICOACHDBMANAGER_H
