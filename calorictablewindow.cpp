#include "calorictablewindow.h"
#include "ui_calorictablewindow.h"



caloricTableWindow::caloricTableWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::caloricTableWindow)
{
    ui->setupUi(this);

    setWindowTitle("CalorieTable");

    connect(ui->lineEdit_foodItemSearch, &QLineEdit::textChanged, this, &caloricTableWindow::on_lineEdit_foodItemSearch_textChanged);

    setupFoodItemsTableWidget();

}

caloricTableWindow::~caloricTableWindow(){
    delete ui;
}

void caloricTableWindow::on_pushButton_changeAddFoodItemPage_clicked(){
    ui->stackedWidget_caloricTable->setCurrentIndex(1);
}

void caloricTableWindow::on_pushButton_cancelAddProduct_clicked(){
    ui->stackedWidget_caloricTable->setCurrentIndex(0);
    ui->lineEdit_foodItemName->clear();
    ui->lineEdit_caloricContent->clear();
    ui->lineEdit_proteinContent->clear();
    ui->lineEdit_fatContent->clear();
    ui->lineEdit_carbohydrateContent->clear();
}

void caloricTableWindow::on_pushButton_addFoodItemToTable_clicked(){
    QString foodName = ui->lineEdit_foodItemName->text();
    QString caloricContentStr = ui->lineEdit_caloricContent->text();
    QString proteinContentStr = ui->lineEdit_proteinContent->text();
    QString fatContentStr = ui->lineEdit_fatContent->text();
    QString carbohydrateContentStr = ui->lineEdit_carbohydrateContent->text();

    if (foodName.isEmpty() || proteinContentStr.isEmpty() ||
        fatContentStr.isEmpty() || carbohydrateContentStr.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Заповніть всі обов'язкові поля.");
        return;
    }

    std::string foodNameStr = foodName.toStdString();
    double proteinContent = proteinContentStr.toDouble();
    double fatContent = fatContentStr.toDouble();
    double carbohydrateContent = carbohydrateContentStr.toDouble();

    FoodItem *foodItem = new FoodItem(foodNameStr, 0, proteinContent, fatContent, carbohydrateContent);

    if (caloricContentStr.isEmpty()) {
        foodItem->calculateCaloricContent();
    } else {
        foodItem->setCaloricContent(caloricContentStr.toInt());
    }

    CaloriCoachDBManager dbManager;
    dbManager.connectToDatabase("localhost", "CaloriCoachDB", "root", 3306);
    dbManager.insertFoodItem(*foodItem);

    ui->stackedWidget_caloricTable->setCurrentIndex(0);
}

void caloricTableWindow::setupFoodItemsTableWidget() {

    ui->tableWidget_foodItem->clearContents();
    ui->tableWidget_foodItem->setRowCount(0);

    QStringList headers = {"Назва продукту", "Калорійність (на 100г)", "Вміст білків (на 100г)", "Вміст жирів (на 100г)", "Вміст вуглеводів (на 100г)"};
    ui->tableWidget_foodItem->setColumnCount(headers.size());
    ui->tableWidget_foodItem->setHorizontalHeaderLabels(headers);

    QSqlQuery query("SELECT foodName, caloricContent, proteinContent, fatContent, carbohydrateContent FROM FoodItems");
    int row = 0;
    while (query.next()) {

        ui->tableWidget_foodItem->insertRow(row);

        for (int col = 0; col < ui->tableWidget_foodItem->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget_foodItem->setItem(row, col, item);
        }

        ++row;
    }
}

void caloricTableWindow::on_lineEdit_foodItemSearch_textChanged(const QString &text) {

    ui->tableWidget_foodItem->clearContents();
    ui->tableWidget_foodItem->setRowCount(0);

    QString searchQuery = "SELECT foodName, caloricContent, proteinContent, fatContent, carbohydrateContent FROM FoodItems WHERE foodName LIKE '%" + text + "%'";
    QSqlQuery query(searchQuery);

    int row = 0;
    while (query.next()) {

        ui->tableWidget_foodItem->insertRow(row);

        for (int col = 0; col < ui->tableWidget_foodItem->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            ui->tableWidget_foodItem->setItem(row, col, item);
        }

        ++row;
    }
}



