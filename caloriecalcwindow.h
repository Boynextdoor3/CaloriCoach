#ifndef CALORIECALCWINDOW_H
#define CALORIECALCWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QVBoxLayout>
#include<QListWidget>
#include "customdish.h"
#include "calorictablewindow.h"
#include "caloricoachdbmanager.h"

namespace Ui {
class CalorieCalcWindow;
}

class CalorieCalcWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CalorieCalcWindow(QWidget *parent = nullptr, int initialTabIndex = 0);
    ~CalorieCalcWindow();

private slots:
    void on_pushButton_addProduct_clicked();
    void on_pushButton_saveDish_clicked();

    void setupCustomDishTableWidget();
    void ChangesTabs();

private:
    Ui::CalorieCalcWindow *ui;
    caloricTableWindow *caloricTableW;
    CaloriCoachDBManager dbManager;
    vector<pair<QString, double>> recipe;

    int currentTabIndex;

};

#endif // CALORIECALCWINDOW_H
