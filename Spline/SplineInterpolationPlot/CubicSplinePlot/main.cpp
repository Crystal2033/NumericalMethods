#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("MainWindow{background-color: rgb(71, 84, 83);}");
    w.show();
    return a.exec();
}
