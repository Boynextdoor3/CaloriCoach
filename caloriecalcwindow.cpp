#include "caloriecalcwindow.h"
#include "ui_caloriecalcwindow.h"

CalorieCalcWindow::CalorieCalcWindow(QWidget *parent, int initialTabIndex) :
    QDialog(parent),
    ui(new Ui::CalorieCalcWindow)
{
    ui->setupUi(this);

    setWindowTitle("CalorieCalc");

    ui->stackedWidget_dishCalc->setCurrentIndex(initialTabIndex);;
    setupCustomDishTableWidget();

}

CalorieCalcWindow::~CalorieCalcWindow()
{
    delete ui;
}


void CalorieCalcWindow::on_pushButton_addProduct_clicked(){
    QString productName = ui->lineEdit_nameProductToAdd->text();

    CaloriCoachDBManager dbManager;

    dbManager.connectToDatabase("localhost", "CaloriCoachDB", "root", 3306);

    FoodItem* foundProduct = dbManager.searchProductByName(productName);

    if (foundProduct) {

        double quantity = ui->lineEdit_guantityOfProduct->text().toDouble();
        recipe.push_back(std::make_pair(productName, quantity));

        QString itemText = productName + " - " + QString::number(quantity);
        new QListWidgetItem(itemText, ui->listWidget_dishProduct);
    } else {
        QMessageBox::warning(this, "Помилка", "Продукт не знайдено");
    }
}



void CalorieCalcWindow::on_pushButton_saveDish_clicked(){
    QString dishName = ui->lineEdit_dishName->text();
    QString dishDescription = ui->lineEdit_dishDescription->text();

    if (dishName.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Введіть назву страви.");
        return;
    }

    CustomDish customDish;
    customDish.setFoodName(dishName.toStdString());
    customDish.setDescription(dishDescription.toStdString());

    double totalCalories = 0.0;
    double totalProtein = 0.0;
    double totalFat = 0.0;
    double totalCarbohydrates = 0.0;

    for (int i = 0; i < ui->listWidget_dishProduct->count(); ++i) {
        QListWidgetItem *item = ui->listWidget_dishProduct->item(i);
        QString itemText = item->text();

        QRegularExpression rx("(.*?) - (\\d+\\.?\\d*)");
        QRegularExpressionMatch match = rx.match(itemText);
        if (match.hasMatch()) {
            QString productName = match.captured(1);
            double quantity = match.captured(2).toDouble();

            CaloriCoachDBManager dbManager;
            dbManager.connectToDatabase("localhost", "CaloriCoachDB", "root", 3306);
            FoodItem* product = dbManager.searchProductByName(productName);

            if (product) {
                totalCalories += (quantity / 100.0) * product->getcaloricContent();
                totalProtein += (quantity / 100.0) * product->getproteinContent();
                totalFat += (quantity / 100.0) * product->getfatContent();
                totalCarbohydrates += (quantity / 100.0) * product->getcarbohydrateContent();

                customDish.addIngredient(productName.toStdString(), quantity);
            } else {
                QMessageBox::warning(this, "Помилка", "Продукт не знайдено в базі даних.");
                return;
            }
        }
    }

    customDish.setCaloricContent(QString::number(totalCalories, 'f', 2).toDouble());
    customDish.setProteinContent(QString::number(totalProtein, 'f', 2).toDouble());
    customDish.setFatContent(QString::number(totalFat, 'f', 2).toDouble());
    customDish.setCarbohydrateContent(QString::number(totalCarbohydrates, 'f', 2).toDouble());
    customDish.setDescription(dishDescription.toStdString());

    CaloriCoachDBManager dbManager;
    dbManager.connectToDatabase("localhost", "CaloriCoachDB", "root", 3306);
    dbManager.insertCustomDish(customDish);

}

void CalorieCalcWindow::setupCustomDishTableWidget() {
    ui->tableWidget_customDish->clearContents();
    ui->tableWidget_customDish->setRowCount(0);

    QStringList headers = {"Назва страви", "Калорійність", "Вміст білків", "Вміст жирів", "Вміст вуглеводів", "Опис", "Рецепт"};
    ui->tableWidget_customDish->setColumnCount(headers.size());
    ui->tableWidget_customDish->setHorizontalHeaderLabels(headers);

    QSqlQuery query("SELECT dishName, caloricContent, proteinContent, fatContent, carbohydrateContent, description, recipe FROM CustomDish");
    int row = 0;
    while (query.next()) {
        ui->tableWidget_customDish->insertRow(row);

        for (int col = 0; col < ui->tableWidget_customDish->columnCount(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());

            if (col == 5 || col == 6) {
                QTextEdit *textEdit = new QTextEdit();
                textEdit->setPlainText(query.value(col).toString());
                ui->tableWidget_customDish->setCellWidget(row, col, textEdit);
            } else {
                ui->tableWidget_customDish->setItem(row, col, item);
            }
        }

        ++row;
    }
}

void CalorieCalcWindow::ChangesTabs() {
    currentTabIndex = 1;
    ui->stackedWidget_dishCalc->setCurrentIndex(currentTabIndex);
}
