#include "adduserwindow.h"
#include "ui_adduserwindow.h"
#include <QDebug>

AddUserWindow::AddUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserWindow)
{
    ui->setupUi(this);
}
AddUserWindow::AddUserWindow(QWidget *parent,QString FirstName, QString SurName, QString g) :
    QDialog(parent),
    ui(new Ui::AddUserWindow)
{
    //QString tmp = "M";
    ui->setupUi(this);
    ui->FirstNameEdit->setText(FirstName);
    ui->SurNameEdit->setText(SurName);

}

void AddUserWindow::accept()
{
    name = ui->FirstNameEdit->text();
    surname = ui->SurNameEdit->text();
    if (ui->MenRadioButton->isChecked())
        g = man;
    else
        g = woman;
    saved=true;
    QDialog::accept(); // zachowanie funkcjonalności
}

AddUserWindow::~AddUserWindow()
{
    delete ui;
}

