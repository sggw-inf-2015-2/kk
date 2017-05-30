#include "userwindow.h"
#include "ui_userwindow.h"
#include <QDesktopWidget>
#include <QHeaderView>
#include <QTableWidget>

UserWindow::UserWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWindow)
{    
    ui->setupUi(this);
    counter = 0;
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rect = desktop->screenGeometry(1);
    move(rect.topLeft());
    this->showMaximized();
    ui->tableWidget->setColumnCount(3);
    QStringList Header;
    Header<<"Imie"<<"Nazwisko"<<"Wynik";
    ui->tableWidget->setHorizontalHeaderLabels(Header);
    ui->tableWidget->setColumnWidth(0,100);
}
UserWindow::~UserWindow()
{
    delete ui;
}
