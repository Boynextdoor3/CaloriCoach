#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    ui->pushButton_changeEditProfilePage->setEnabled(false);

    ui->comboBox_changeUserPlan->addItems({"Схуднення", "Підтримання маси", "Набір маси"});
    ui->comboBox_editUserPlan->addItems({"Схуднення", "Підтримання маси", "Набір маси"});

    CaloriCoachDBManager dbManager;
    dbManager.connectToDatabase("localhost", "CaloriCoachDB", "root", 3306);
    dbManager.createTables();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_changeProfilePage_clicked(){
    ui->stackedWidget_Main->setCurrentIndex(0);
}

void MainWindow::on_pushButton_changeCreateProfilePage_clicked(){
    ui->stackedWidget_Main->setCurrentIndex(2);
}

void MainWindow::on_pushButton_changeEditProfilePage_clicked(){
    ui->stackedWidget_Main->setCurrentIndex(1);
}

void MainWindow::on_pushButton_openCaloriTableWindow_clicked(){
    caloricTableW = new caloricTableWindow(this);
    caloricTableW->show();
}


void MainWindow::on_pushButton_openCalorieCalcWindow_clicked(){
    calorieCalcW = new CalorieCalcWindow(this, 0);
    calorieCalcW->show();
}


void MainWindow::on_pushButton_changeDishViewPage_clicked(){
    calorieCalcW = new CalorieCalcWindow(this, 1);
    calorieCalcW->show();
}

void MainWindow::on_pushButton_createProfile_clicked(){
    QString userName = ui->lineEdit_enterUserName->text();
    QString userWeightStr = ui->lineEdit_enterUserWeight->text();
    QString userGoalStr = ui->lineEdit_enterUserGoal->text();
    QString selectedPlan = ui->comboBox_changeUserPlan->currentText();

    if (userName.isEmpty() || userWeightStr.isEmpty()) {
        QMessageBox::critical(this, "Помилка", "Заповніть всі поля");
        return;
    }

    double userWeight = userWeightStr.toDouble();
    double userGoal = (selectedPlan == "Підтримання маси") ? 0.0 : userGoalStr.toDouble();

    if (selectedPlan == "Схуднення" && userWeight <= userGoal) {
        QMessageBox::critical(this, "Помилка", "Для плану схуднення вага повинна бути більше цілевої ваги");
        return;
    } else if (selectedPlan == "Підтримання маси") {
        ui->lineEdit_enterUserGoal->setEnabled(false);
    } else if (selectedPlan == "Набір маси" && userWeight >= userGoal) {
        QMessageBox::critical(this, "Помилка", "Для плану набору маси вага повинна бути менше цілевої ваги");
        return;
    }

    string userPlan = selectedPlan.toStdString();
    UserProfile userProfile(userName.toStdString(), userWeight, userGoal, userPlan);

    CaloriCoachDBManager dbManager;
    dbManager.connectToDatabase("localhost", "CaloriCoachDB", "root", 3306);
    dbManager.insertUserProfile(userProfile);

    ui->profileNamelabel->setText(QString::fromStdString(userProfile.getUserName()));
    ui->profileWeightLabel->setText(QString::number(userProfile.getUserWeight()));
    ui->profilePlanlabel->setText(QString::fromStdString(userProfile.getUserPlan()));
    ui->profileGoalLabel->setText(QString::number(userProfile.getUserGoal()));

    int caloricDayNorm = 0;

    if (selectedPlan == "Схуднення") {
        caloricDayNorm = static_cast<int>(userWeight * 22);
    } else if (selectedPlan == "Підтримання маси") {
        caloricDayNorm = static_cast<int>(userWeight * 24);
    } else if (selectedPlan == "Набір маси") {
        caloricDayNorm = static_cast<int>(userWeight * 26);
    }

    double proteinDayNorm = (0.15 * caloricDayNorm) / 4;
    double fatDayNorm = (0.20 * caloricDayNorm) / 9;
    double carbohydrateDayNorm = ((0.65 * caloricDayNorm) - (proteinDayNorm * 4) - (fatDayNorm * 9)) / 4;

    ui->label_caloricDayNorm->setText(QString::number(caloricDayNorm));
    ui->label_proteinDayNorm->setText(QString::number(proteinDayNorm, 'f', 1));
    ui->label_fatDayNorm->setText(QString::number(fatDayNorm, 'f', 1));
    ui->label_carbohydrateDayNorm->setText(QString::number(carbohydrateDayNorm, 'f', 1));

    ui->stackedWidget_Main->setCurrentIndex(0);
    ui->pushButton_changeEditProfilePage->setEnabled(true);
    ui->pushButton_changeCreateProfilePage->deleteLater();
}



void MainWindow::on_pushButton_editProfile_clicked(){
    QString userName = ui->lineEdit_editUserName->text();
    QString userWeightStr = ui->lineEdit_editUserWeight->text();
    QString userGoalStr = ui->lineEdit_editUserGoal->text();
    QString selectedPlan = ui->comboBox_editUserPlan->currentText();

    if (userName.isEmpty() || userWeightStr.isEmpty() || userGoalStr.isEmpty() || selectedPlan.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Заповніть всі поля.");
        return;
    }

    double editedUserWeight = userWeightStr.toDouble();
    double editedUserGoal = (selectedPlan == "Підтримання маси") ? 0.0 : userGoalStr.toDouble();

    CaloriCoachDBManager dbManager;
    dbManager.connectToDatabase("localhost", "CaloriCoachDB", "root", 3306);

    if (dbManager.updateUserProfile(userName, editedUserWeight, editedUserGoal, selectedPlan)) {
        QMessageBox::information(this, "Інформація", "Профіль успішно оновлено.");
    } else {
        QMessageBox::warning(this, "Помилка", "Помилка при оновленні профілю.");
    }

    ui->profileNamelabel->setText(userName);
    ui->profileWeightLabel->setText(QString::number(editedUserWeight));
    ui->profilePlanlabel->setText(selectedPlan);
    ui->profileGoalLabel->setText(QString::number(editedUserGoal));

    int caloricDayNorm = 0;

    if (selectedPlan == "Схуднення") {
        caloricDayNorm = static_cast<int>(editedUserWeight * 22);
    } else if (selectedPlan == "Підтримання маси") {
        caloricDayNorm = static_cast<int>(editedUserWeight * 24);
    } else if (selectedPlan == "Набір маси") {
        caloricDayNorm = static_cast<int>(editedUserWeight * 26);
    }

    double proteinDayNorm = (0.15 * caloricDayNorm) / 4;
    double fatDayNorm = (0.20 * caloricDayNorm) / 9;
    double carbohydrateDayNorm = ((0.65 * caloricDayNorm) - (proteinDayNorm * 4) - (fatDayNorm * 9)) / 4;

    ui->label_caloricDayNorm->setText(QString::number(caloricDayNorm));
    ui->label_proteinDayNorm->setText(QString::number(proteinDayNorm, 'f', 1));
    ui->label_fatDayNorm->setText(QString::number(fatDayNorm, 'f', 1));
    ui->label_carbohydrateDayNorm->setText(QString::number(carbohydrateDayNorm, 'f', 1));

}


void MainWindow::on_pushButton_cancelProfileEdit_clicked(){
    ui->stackedWidget_Main->setCurrentIndex(0);
    ui->lineEdit_editUserName->clear();
    ui->lineEdit_editUserWeight->clear();
    ui->lineEdit_editUserGoal->clear();
}


void MainWindow::on_pushButton_closeApp_clicked()
{
    qApp->quit();
}

