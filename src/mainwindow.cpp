#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <cstdlib>

MainWindow::MainWindow(UserWindow *uw, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userWindow = uw;
    recordOnRun = false;
    initialiseDeviceList();

    connect(ui->recordButton, SIGNAL(pressed()), this, SLOT(proceed()));
	connect(&recorder, SIGNAL(recordingStopped(qint64)), this, SLOT(onRecordingStopped(qint64)));
	connect(ui->deviceComboBox, SIGNAL(currentTextChanged(QString)), &recorder, SLOT(InitialiseRecorder(QString)));

    ui->AdminUserList->setColumnCount(5);
    QStringList Header;
    Header<<"Imię"<<"Nazwisko"<<"Płeć"<<"Wynik"<<"Czy było ponowne podejście?";
    ui->AdminUserList->setHorizontalHeaderLabels(Header);
    ui->AdminUserList->horizontalHeader()->setStretchLastSection(true); // Resize last column to fit QTableWidget edge.
    ui->AllRadioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::proceed()
{
    int rowindex = ui->AdminUserList->selectionModel()->currentIndex().row();
	try
    {    if (rowindex >= 0)
         {
            if (ui->AdminUserList->item(rowindex,4)->checkState() == Qt::Unchecked)
            {
                if (ui->AdminUserList->item(rowindex,3)->data(Qt::DisplayRole).toDouble() != 0.0)
                {
                    ui->AdminUserList->item(rowindex,4)->setCheckState(Qt::Checked);
                }
                double x = (double)(rand() % 121); // Just for test purpose. To be deleted when audio model would be done.
                User::setShoutScore(rowindex,x);
                userWindow->InsertUserToRanking(User::GetUser(rowindex),rowindex);
                ui->AdminUserList->setItem(rowindex,3,new QTableWidgetItem(QString::number(x))); // Update shout score in adminWindow's table.
                /*if (!recordOnRun)
                {
                    recorder.Start();
                    recordOnRun = true;
                    ui->recordButton->setText(tr("Zatrzymaj"));
                    ui->bytes->clear();
                    ui->deviceComboBox->setEnabled(false);
                }
                else
                {
                    recorder.Stop();
                }*/
            }
            else
            {
                QMessageBox::information(this, windowTitle(), tr("Ten użytkownik wyczerpał już swój limit podejść."));
            }
        }
        else
        {
            QMessageBox::information(this, windowTitle(), tr("Zaznacz użytkownika, od którego chcesz pobrać próbkę krzyku."));
        }
	}
	catch (exception &e)
	{
		QMessageBox::critical(this, windowTitle(), e.what());
		return;
	}
}

void MainWindow::onRecordingStopped(qint64 size)
{
	ui->bytes->setText(QString::number((long)size) + tr(" bajtów"));
	ui->recordButton->setText(tr("Nagrywaj"));
	recordOnRun = false;
}

void MainWindow::initialiseDeviceList()
{
    auto devices = recorder.GetAvailableDevices();
    if (devices.isEmpty())
    {
        // Set 'Nagrywaj' button and device list as disabled, so that user could not interact with them.
        ui->deviceComboBox->setEnabled(false);
        ui->recordButton->setEnabled(false);
        QMessageBox::critical(this, windowTitle(), tr("Nie znaleziono żadnych urządzeń do nagrywania. Sprawdź swoje ustawienia i uruchom program ponownie."));
    }
    else
    {
        ui->deviceComboBox->addItems(devices);
    }
}

void MainWindow::insertUserToList(User * const user)
{
    int row = ui->AdminUserList->rowCount() - 1;
    ui->AdminUserList->setItem(row, 0, new QTableWidgetItem(user->getFirstName()));
    ui->AdminUserList->setItem(row, 1, new QTableWidgetItem(user->getLastName()));
    QString g = user->getPersonGender() == man ? "M" : "K";
    ui->AdminUserList->setItem(row, 2, new QTableWidgetItem(g));
    ui->AdminUserList->setItem(row, 3, new QTableWidgetItem(QString::number(user->getShoutScore())));

    auto *checkBoxCell = new QTableWidgetItem(); // Need to assign QTableWidgetItem's address to a pointer in order to call next two functions
    // Do not worry about 'new' operator, QTableWidget can handle this.
    checkBoxCell->data(Qt::CheckStateRole);
    checkBoxCell->setCheckState(Qt::Unchecked);
    ui->AdminUserList->setItem(row, 4, checkBoxCell);
}


void MainWindow::on_AddUserButton_clicked()
{
   auw = new AddUserWindow(this);
   if (auw->exec() == 1) // exec returns 1 when accepted.
   {
       User U(auw->GetName(), auw->GetSurName(), auw->GetGender(),0);
       ui->AdminUserList->setRowCount(ui->AdminUserList->rowCount()+1);
       insertUserToList(&U);
   }
   delete auw;
}

void MainWindow::on_EditUserButton_clicked()
{
    QString Name;
    QString SurName;
    QString genderText;
    gender g;

    int rowidx = ui->AdminUserList->selectionModel()->currentIndex().row();
    if (rowidx < 0) // Nothing was selected.
    {
        QMessageBox::information(this, windowTitle(), tr("Zaznacz użytkownika, którego dane chcesz zedytować i spróbuj ponownie."));
        return;
    }

    Name = ui->AdminUserList->item(rowidx,0)->text();
    SurName = ui->AdminUserList->item(rowidx,1)->text();
    genderText = ui->AdminUserList->item(rowidx,2)->text();
    g = genderText == "M" ? man : woman;

    auw = new AddUserWindow(this,Name,SurName,g);
    if (auw->exec() == 1)
    {
        if (auw->GetGender()==man)
            genderText = "M";
        else
            genderText = "K";
        User::editUser(rowidx,auw->GetName(),auw->GetSurName(),auw->GetGender());
        ui->AdminUserList->setItem(rowidx,0,new QTableWidgetItem(auw->GetName()));
        ui->AdminUserList->setItem(rowidx,1,new QTableWidgetItem(auw->GetSurName()));
        ui->AdminUserList->setItem(rowidx,2,new QTableWidgetItem(genderText));
    }
    delete auw;
}

void MainWindow::on_ExportUsersDataButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(
                    this, "Zapisz plik","","*.csv");
    filename.append(".csv");
    if (filename == "")
        return;
    User::exportToCSV(filename);
}

void MainWindow::on_ImportUsersDataButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, windowTitle(), tr("Zaimportowanie nowych danych spowoduje utratę wszystkich niezapisanych danych. Czy kontynuować?"),
                                   QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No)
    {
       return;
    }

    QString filename = QFileDialog::getOpenFileName(
                this, tr(""),"","Wszystkie pliki (*.*);;Pliki eksportu (*.csv))");
    if (filename == "")
        return;
    auto users = User::importFromCSV(filename);

    ui->AdminUserList->clearContents();
    ui->AdminUserList->setRowCount(0);
    userWindow->ClearRanking();

    for (auto user : users)
    {
        ui->AdminUserList->setRowCount(ui->AdminUserList->rowCount() + 1);
        insertUserToList(user);
        if (user->getShoutScore() != 0.0)
            userWindow->InsertUserToRanking(user, ui->AdminUserList->rowCount() - 1);
    }
}

void MainWindow::on_MenRadioButton_toggled(bool checked)
{
    userWindow->ShowAll();
    userWindow->SetShowing(m);
    userWindow->HideWomen();
}

void MainWindow::on_WomenRadioButton_toggled(bool checked)
{
    userWindow->ShowAll();
    userWindow->SetShowing(w);
    userWindow->HideMen();
}

void MainWindow::on_AllRadioButton_toggled(bool checked)
{
    userWindow->ShowAll();
    userWindow->SetShowing(a);
}
