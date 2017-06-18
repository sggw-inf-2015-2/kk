#include "mainwindow.h"
#include "userwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QTranslator qtTranslator;
	if (qtTranslator.load("translations/qt_" + QLocale::system().name()))
		a.installTranslator(&qtTranslator);

    UserWindow uw;
    MainWindow w(&uw);
    w.show();
    uw.show();
    return a.exec();
}
