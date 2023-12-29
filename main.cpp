#include "mainwindow.h"
#include <QStyleFactory>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setStyle(QStyleFactory::create("Fusion"));

    w.setWindowTitle("CaloriCoach");
    w.setWindowIcon(QIcon(":/img/img/cutlery.png"));

    w.show();
    return a.exec();

}
