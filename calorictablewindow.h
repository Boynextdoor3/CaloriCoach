#ifndef CALORICTABLEWINDOW_H
#define CALORICTABLEWINDOW_H

#include <QTableWidgetItem>
#include <QDialog>
#include "fooditem.h"
#include "caloricoachdbmanager.h"



namespace Ui {
class caloricTableWindow;
}

class caloricTableWindow : public QDialog
{
    Q_OBJECT

public:
    explicit caloricTableWindow(QWidget *parent = nullptr);
    ~caloricTableWindow();

private slots:
    void on_pushButton_changeAddFoodItemPage_clicked();
    void on_pushButton_addFoodItemToTable_clicked();
    void on_pushButton_cancelAddProduct_clicked();

    void setupFoodItemsTableWidget();

    void on_lineEdit_foodItemSearch_textChanged(const QString &text);

private:
    Ui::caloricTableWindow *ui;

    CaloriCoachDBManager dbManager;


};

#endif // CALORICTABLEWINDOW_H
