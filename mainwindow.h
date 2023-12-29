#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "caloricoachdbmanager.h"
#include "calorictablewindow.h"
#include "caloriecalcwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_changeProfilePage_clicked();
    void on_pushButton_changeCreateProfilePage_clicked();
    void on_pushButton_createProfile_clicked();
    void on_pushButton_openCaloriTableWindow_clicked();
    void on_pushButton_openCalorieCalcWindow_clicked();
    void on_pushButton_changeDishViewPage_clicked();
    void on_pushButton_changeEditProfilePage_clicked();
    void on_pushButton_editProfile_clicked();


    void on_pushButton_cancelProfileEdit_clicked();

    void on_pushButton_closeApp_clicked();

private:
    Ui::MainWindow *ui;

    caloricTableWindow *caloricTableW;
    CalorieCalcWindow *calorieCalcW;

    int caloricDayNorm;
    double proteinDayNorm;
    double fatDayNorm;
    double carbohydrateDayNorm;


};
#endif // MAINWINDOW_H
