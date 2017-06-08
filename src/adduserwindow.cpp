#include "adduserwindow.h"
#include "ui_adduserwindow.h"

AddUserWindow::AddUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Dodaj użytkownika"));
    setFixedSize(size());
}

AddUserWindow::AddUserWindow(QWidget *parent,QString FirstName, QString SurName, gender g) :
    QDialog(parent),
    ui(new Ui::AddUserWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Edytuj użytkownika"));
    setFixedSize(size());

    ui->FirstNameEdit->setText(FirstName);
    ui->SurNameEdit->setText(SurName);
    if (g == man)
        ui->MenRadioButton->setChecked(true);
    else
        ui->WomenRadioButton->setChecked(true);
}

void AddUserWindow::accept()
{
    name = ui->FirstNameEdit->text();
    surname = ui->SurNameEdit->text();
    if (ui->MenRadioButton->isChecked())
        g = man;
    else
        g = woman;
    QDialog::accept();
}

AddUserWindow::~AddUserWindow()
{
    delete ui;
}

