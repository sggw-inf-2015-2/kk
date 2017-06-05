#include "adduserwindow.h"
#include "ui_adduserwindow.h"

AddUserWindow::AddUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserWindow)
{
    ui->setupUi(this);
}

void AddUserWindow::accept()
{
    name = ui->FirstNameEdit->text();
    surname = ui->SurNameEdit->text();
    if (ui->MenRadioButton->isChecked() == Qt::Checked)
        g = man;
    else
        g = woman;
    QDialog::accept(); // zachowanie funkcjonalności
}

AddUserWindow::~AddUserWindow()
{
    delete ui;
}

