#include "userwindow.h"
#include "ui_userwindow.h"
#include <QDesktopWidget>
#include <QHeaderView>
#include <QTableWidget>
#include <QDebug>


UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{    
    ui->setupUi(this);
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rect = desktop->screenGeometry(1);
    move(rect.topLeft());
    this->showMaximized();

    setCentralWidget(ui->UserList);
    ui->UserList->setColumnCount(4);
    // ui->UserList->setColumnHidden(3, true);
    QStringList Header;
    Header<<"Imię"<<"Nazwisko"<<"Wynik";
    ui->UserList->setHorizontalHeaderLabels(Header);
    //ui->UserList->horizontalHeader()->setSortIndicator(2, Qt::DescendingOrder); // Enable default sorting by 'score' column. There is also a ability to chose sorting by either name or surname.
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::resizeEvent(QResizeEvent *event)
{
    ui->UserList->setColumnWidth(0, this->width() * 0.4);
    ui->UserList->setColumnWidth(1, this->width() * 0.4);
    ui->UserList->setColumnWidth(2, this->width() * 0.2);

    QMainWindow::resizeEvent(event);
}

void UserWindow::InsertUserToRanking(User *user, int ID)
{
    qDebug() << ID;
     for(int i=0;i<ui->UserList->rowCount();i++)
     {
         if (ui->UserList->item(i,3)->text() == QString::number(ID))
         {
             ui->UserList->setItem(i,0,new QTableWidgetItem(user->getFirstName()));
             ui->UserList->setItem(i,1,new QTableWidgetItem(user->getLastName()));
             ui->UserList->setItem(i,2,new QTableWidgetItem(QString::number(user->getShoutScore())));
             //ui->UserList->sortByColumn(2);
             return;
         }
     }
     ui->UserList->setRowCount(ui->UserList->rowCount()+1);
     ui->UserList->setItem(ui->UserList->rowCount()-1,0,new QTableWidgetItem(user->getFirstName()));
     ui->UserList->setItem(ui->UserList->rowCount()-1,1,new QTableWidgetItem(user->getLastName()));
     ui->UserList->setItem(ui->UserList->rowCount()-1,2,new QTableWidgetItem(QString::number(user->getShoutScore())));
     ui->UserList->setItem(ui->UserList->rowCount()-1,3,new QTableWidgetItem(QString::number(ID)));
     ui->UserList->sortByColumn(2);
}


