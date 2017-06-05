#include "mainwindow.h"
#include "userwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UserWindow uw;
    MainWindow w(&uw);
    w.show();
    uw.show();
    return a.exec();
}
