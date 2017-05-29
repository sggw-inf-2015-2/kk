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
//    ui->tableWidget->setItem(0,0,new QTableWidgetItem("Test"));
//    ui->tableWidget->setItem(1,0,new QTableWidgetItem("Test"));
//    ui->tableWidget->setItem(2,0,new QTableWidgetItem("Test"));
//    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}
UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->tableWidget->setItem(counter++,0,new QTableWidgetItem("Test"));
}
