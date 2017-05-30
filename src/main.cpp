#include "mainwindow.h"
#include "userwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    UserWindow uw;
    w.show();
    uw.show();
    return a.exec();
}
