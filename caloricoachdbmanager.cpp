#include "caloricoachdbmanager.h"


CaloriCoachDBManager::CaloriCoachDBManager() {
}


void CaloriCoachDBManager::connectToDatabase(const QString &host, const QString &dbName, const QString &user, int port){

    CaloriCoach_DB = QSqlDatabase::addDatabase("QMYSQL");


    CaloriCoach_DB.setHostName(host);
    CaloriCoach_DB.setPort(port);
    CaloriCoach_DB.setDatabaseName(dbName);
    CaloriCoach_DB.setUserName(user);


    if (CaloriCoach_DB.open()) {
         qDebug() <<"Connected to database";
    } else {
         qDebug() << "Database is not open.";
    }
}

void CaloriCoachDBManager::createTables(){
    if (!CaloriCoach_DB.isOpen()) {
        qDebug() << "Database is not open. Unable to create tables.";
        return;
    }


    QSqlQuery userProfileQuery;
    QString userProfileTableQuery = "CREATE TABLE IF NOT EXISTS UserProfiles ("
                                    "id INT AUTO_INCREMENT PRIMARY KEY, "
                                    "userName VARCHAR(255) NOT NULL, "
                                    "userWeight DOUBLE NOT NULL, "
                                    "userPlan VARCHAR(255), "
                                    "userGoal DOUBLE)";
    if (userProfileQuery.exec(userProfileTableQuery)) {
        qDebug() << "Table UserProfiles created or already exists";
    } else {
        qDebug() << "Error creating table UserProfiles:" << userProfileQuery.lastError().text();
    }

    QSqlQuery foodItemsQuery;
    QString foodItemsTableQuery = "CREATE TABLE IF NOT EXISTS FoodItems ("
                                  "id INT AUTO_INCREMENT PRIMARY KEY, "
                                  "foodName VARCHAR(255) NOT NULL, "
                                  "caloricContent INT NOT NULL, "
                                  "proteinContent DOUBLE NOT NULL, "
                                  "fatContent DOUBLE NOT NULL, "
                                  "carbohydrateContent DOUBLE NOT NULL)";
    if (foodItemsQuery.exec(foodItemsTableQuery)) {
        qDebug() << "Table FoodItems created or already exists";
    } else {
        qDebug() << "Error creating table FoodItems:" << foodItemsQuery.lastError().text();
    }

    QSqlQuery customDishQuery;
    QString customDishTableQuery = "CREATE TABLE IF NOT EXISTS CustomDish ("
                                   "id INT AUTO_INCREMENT PRIMARY KEY, "
                                   "dishName VARCHAR(255) NOT NULL, "
                                   "description TEXT, "
                                   "caloricContent DOUBLE NOT NULL, "
                                   "proteinContent DOUBLE NOT NULL, "
                                   "fatContent DOUBLE NOT NULL, "
                                   "carbohydrateContent DOUBLE NOT NULL, "
                                   "recipe TEXT)";
    if (customDishQuery.exec(customDishTableQuery)) {
        qDebug() << "Table CustomDish created or already exists";
    } else {
        qDebug() << "Error creating table CustomDish:" << customDishQuery.lastError().text();
    }
}

void CaloriCoachDBManager::insertUserProfile(const UserProfile &userProfile){

    if (!CaloriCoach_DB.isOpen()) {
        qDebug() << "Database is not open. Unable to insert user profile.";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO UserProfiles (userName, userWeight, userPlan, userGoal) "
                  "VALUES (:userName, :userWeight, :userPlan, :userGoal)");

    query.bindValue(":userName", QString::fromStdString(userProfile.getUserName()));
    query.bindValue(":userWeight", userProfile.getUserWeight());
    query.bindValue(":userPlan", QString::fromStdString(userProfile.getUserPlan()));
    query.bindValue(":userGoal", userProfile.getUserGoal());

    if (query.exec()) {
        qDebug() << "User profile inserted successfully.";
    } else {
        qDebug() << "Error inserting user profile:" << query.lastError().text();
    }
}

void CaloriCoachDBManager::insertFoodItem(const FoodItem &foodItem) {
    if (!CaloriCoach_DB.isOpen()) {
        qDebug() << "Database is not open. Unable to insert food item.";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO FoodItems (foodName, caloricContent, proteinContent, fatContent, carbohydrateContent) "
                  "VALUES (:foodName, :caloricContent, :proteinContent, :fatContent, :carbohydrateContent)");
    query.bindValue(":foodName", QString::fromStdString(foodItem.getfoodName()));
    query.bindValue(":caloricContent", foodItem.getcaloricContent());
    query.bindValue(":proteinContent", foodItem.getproteinContent());
    query.bindValue(":fatContent", foodItem.getfatContent());
    query.bindValue(":carbohydrateContent", foodItem.getcarbohydrateContent());

    if (query.exec()) {
        qDebug() << "Food item inserted into database.";
    } else {
        qDebug() << "Error inserting food item into database:" << query.lastError().text();
    }
}

FoodItem* CaloriCoachDBManager::searchProductByName(const QString& productName){

    QSqlQuery query;
    query.prepare("SELECT * FROM FoodItems WHERE foodName = :name");
    query.bindValue(":name", productName);

    if (query.exec() && query.next()) {
        QString name = query.value("foodName").toString();
        int caloricContent = query.value("caloricContent").toInt();
        double proteinContent = query.value("proteinContent").toDouble();
        double fatContent = query.value("fatContent").toDouble();
        double carbohydrateContent = query.value("carbohydrateContent").toDouble();

        FoodItem* foundProduct = new FoodItem(name.toStdString(), caloricContent, proteinContent, fatContent, carbohydrateContent);
        return foundProduct;
    }

    return nullptr;
}

void CaloriCoachDBManager::insertCustomDish(const CustomDish &customDish){
    if (!CaloriCoach_DB.isOpen()) {
        qDebug() << "Database is not open. Unable to insert CustomDish.";
        return;
    }

    QSqlQuery query;

    QString insertQuery = "INSERT INTO CustomDish (dishName, description, caloricContent, proteinContent, fatContent, carbohydrateContent, recipe) "
                          "VALUES (:dishName, :description, :caloricContent, :proteinContent, :fatContent, :carbohydrateContent, :recipe)";

    query.prepare(insertQuery);

    query.bindValue(":dishName", QString::fromStdString(customDish.getfoodName()));
    query.bindValue(":description", QString::fromStdString(customDish.getDescription()));
    query.bindValue(":caloricContent", customDish.getcaloricContent());
    query.bindValue(":proteinContent", customDish.getproteinContent());
    query.bindValue(":fatContent", customDish.getfatContent());
    query.bindValue(":carbohydrateContent", customDish.getcarbohydrateContent());

    QString recipeText;
    for (const auto &ingredient : customDish.getRecipe()) {
        recipeText += QString("%1 - %2\n").arg(QString::fromStdString(ingredient.first)).arg(ingredient.second);
    }
    query.bindValue(":recipe", recipeText.trimmed());

    if (query.exec()) {
        qDebug() << "CustomDish inserted successfully.";
    } else {
        qDebug() << "Error inserting CustomDish:" << query.lastError().text();
    }
}

bool CaloriCoachDBManager::updateUserProfile(const QString& userName, double userWeight, double userGoal, const QString& userPlan) {

    QSqlQuery query;
    query.prepare("UPDATE UserProfiles SET UserWeight = :userWeight, UserGoal = :userGoal, UserPlan = :userPlan WHERE UserName = :userName");
    query.bindValue(":userWeight", userWeight);
    query.bindValue(":userGoal", userGoal);
    query.bindValue(":userPlan", userPlan);
    query.bindValue(":userName", userName);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Помилка при оновленні профілю користувача:" << query.lastError().text();
        return false;
    }
}

