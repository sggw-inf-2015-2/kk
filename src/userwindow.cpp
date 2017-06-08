#include "userwindow.h"
#include "ui_userwindow.h"
#include <QDesktopWidget>
#include <QHeaderView>
#include <QTableWidget>

UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{    
    ui->setupUi(this);
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rect = desktop->screenGeometry(1);
    move(rect.topLeft());
    this->showMaximized();

    setCentralWidget(ui->tableWidget);
    ui->tableWidget->setColumnCount(3);
    QStringList Header;
    Header<<"Imię"<<"Nazwisko"<<"Wynik";
    ui->tableWidget->setHorizontalHeaderLabels(Header);
    ui->tableWidget->sortByColumn(2); // Enable default sorting by 'score' column. There is also a ability to chose sorting by either name or surname.
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::resizeEvent(QResizeEvent *event)
{
    ui->tableWidget->setColumnWidth(0, this->width() * 0.4);
    ui->tableWidget->setColumnWidth(1, this->width() * 0.4);
    ui->tableWidget->setColumnWidth(2, this->width() * 0.2);

    QMainWindow::resizeEvent(event);
}
