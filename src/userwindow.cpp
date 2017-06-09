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

    setCentralWidget(ui->UserList);
    ui->UserList->setColumnCount(5);
    ui->UserList->setColumnHidden(3, true); // Hide ID column.
    ui->UserList->setColumnHidden(4, true); // Hide gender column.
    QStringList Header;
    Header << "Imię" << "Nazwisko" << "Wynik [dB]";
    ui->UserList->setHorizontalHeaderLabels(Header);
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
     for(int i=0;i<ui->UserList->rowCount();i++)
     {
         if (ui->UserList->item(i,3)->text() == QString::number(ID))
         {
             ui->UserList->setItem(i,0,new QTableWidgetItem(user->getFirstName()));
             ui->UserList->setItem(i,1,new QTableWidgetItem(user->getLastName()));
             auto item = new QTableWidgetItem();
             item->setData(Qt::DisplayRole, QVariant(user->getShoutScore()));
             ui->UserList->setItem(i,2,item);
             QString genderText = user->getPersonGender() == man ? "M" : "K";
             ui->UserList->setItem(ui->UserList->rowCount()-1,4,new QTableWidgetItem(genderText));
             ui->UserList->sortByColumn(2);
             return;
         }
     }
     ui->UserList->setRowCount(ui->UserList->rowCount()+1);
     ui->UserList->setItem(ui->UserList->rowCount()-1,0,new QTableWidgetItem(user->getFirstName()));
     ui->UserList->setItem(ui->UserList->rowCount()-1,1,new QTableWidgetItem(user->getLastName()));
     auto item = new QTableWidgetItem();
     item->setData(Qt::DisplayRole, QVariant(user->getShoutScore()));
     ui->UserList->setItem(ui->UserList->rowCount()-1,2,item);
     ui->UserList->setItem(ui->UserList->rowCount()-1,3,new QTableWidgetItem(QString::number(ID)));
     QString genderText = user->getPersonGender() == man ? "M" : "K";
     ui->UserList->setItem(ui->UserList->rowCount()-1,4,new QTableWidgetItem(genderText));
     ui->UserList->sortByColumn(2);
}

void UserWindow::ClearRanking()
{
    ui->UserList->clearContents();
}
