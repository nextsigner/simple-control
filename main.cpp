#include "mainwindow.h"
#include <QApplication>

int main(int cant, char *argv[])
{
    QApplication a(cant, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
