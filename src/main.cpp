#include "mainwindow.h"
#include "userwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QTranslator qtTranslator;
	if (qtTranslator.load(QLocale::system(), "qt", "_",
						  QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
		a.installTranslator(&qtTranslator);

    UserWindow uw;
    MainWindow w(&uw);
    w.show();
    uw.show();
    return a.exec();
}
