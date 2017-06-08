#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::proceed()
{
	try
	{
		if (!recordOnRun)
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


void MainWindow::on_AddUserButton_clicked()
{
   auw = new AddUserWindow(this);
   if (auw->exec() == 1) // exec returns 1 when accepted.
   {
       User U(auw->GetName(), auw->GetSurName(), auw->GetGender(),0);
       ui->AdminUserList->setRowCount(ui->AdminUserList->rowCount()+1);
       ui->AdminUserList->setItem(ui->AdminUserList->rowCount()-1,0,new QTableWidgetItem(U.getFirstName()));
       ui->AdminUserList->setItem(ui->AdminUserList->rowCount()-1,1,new QTableWidgetItem(U.getLastName()));
       QString g;
       if (U.getPersonGender()==man)
           g="M";
       else
           g="K";
       ui->AdminUserList->setItem(ui->AdminUserList->rowCount()-1,2,new QTableWidgetItem(g));
       ui->AdminUserList->setItem(ui->AdminUserList->rowCount()-1,3, new QTableWidgetItem(QString::number(U.getShoutScore())));

       auto *checkBoxCell = new QTableWidgetItem(); // Need to assign QTableWidgetItem's address to a pointer in order to call next two functions
       // Do not worry about 'new' operator, QTableWidget can handle this.
       checkBoxCell->data(Qt::CheckStateRole);
       checkBoxCell->setCheckState(Qt::Unchecked);
       ui->AdminUserList->setItem(ui->AdminUserList->rowCount()-1, 4, checkBoxCell);
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
