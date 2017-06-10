#include "adduserwindow.h"
#include "ui_adduserwindow.h"
#include <QMessageBox>

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
    if (!(ui->FirstNameEdit->text().isEmpty()))
    {
         name = ui->FirstNameEdit->text();
         if (!(ui->SurNameEdit->text().isEmpty()))
         {
               surname = ui->SurNameEdit->text();
               (ui->MenRadioButton->isChecked()) ? g=man :g=woman;
                QDialog::accept();
         }
         else
         {
            QMessageBox::critical(this, windowTitle(), tr("Pole nazwisko jest puste"));
         }
    }
    else
    {
         QMessageBox::critical(this, windowTitle(), tr("Pole imię jest puste"));
    }
}

AddUserWindow::~AddUserWindow()
{
    delete ui;
}

