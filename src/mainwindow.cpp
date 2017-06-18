#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audiomodel.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(UserWindow *uw, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	setFixedSize(size());
    userWindow = uw;
    recordOnRun = false;
	calibrator = new Calibrator(&recorder, this);
    initialiseDeviceList();

    connect(ui->recordButton, SIGNAL(pressed()), this, SLOT(proceed()));
	connect(ui->deviceComboBox, SIGNAL(currentTextChanged(QString)), &recorder, SLOT(InitialiseRecorder(QString)));
	connect(calibrator, SIGNAL(calibrationStopped()), this, SLOT(onCalibrationStopped()));

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
	delete calibrator;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, tr("Zamykanie programu"), tr("Czy chcesz eksportować listę do pliku przed zamknięciem?"), QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
	if (resBtn == QMessageBox::Cancel)
	{
		event->ignore();
	}
	else if (resBtn == QMessageBox::Yes)
	{
		on_actionExportToCsv_triggered();
		event->accept();
		userWindow->close();
	}
	else
	{
		event->accept();
		userWindow->close();
	}
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
				if (!recordOnRun)
                {
					connect(&recorder, SIGNAL(recordingStopped(const QVector<std::complex<double> > &)), this, SLOT(onRecordingStopped(const QVector<std::complex<double> > &)));
					currentUser = rowindex; // onRecordingStopped() slot must know, to which user it should assigns shout level.
                    recorder.Start();
                    recordOnRun = true;
                    ui->recordButton->setText(tr("Zatrzymaj"));
                    ui->deviceComboBox->setEnabled(false);
                }
                else
                {
                    recorder.Stop();
				}
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

void MainWindow::onRecordingStopped(const QVector<std::complex<double> > &complexData)
{
    qDebug() << Calibrator::calibrationData;
    double result = AudioModel::computeLevel(complexData, Calibrator::calibrationData);

	User::setShoutScore(currentUser, result);
	userWindow->InsertUserToRanking(User::GetUser(currentUser), currentUser);
	ui->AdminUserList->setItem(currentUser,3,new QTableWidgetItem(QString::number(result))); // Update shout score in adminWindow's table.
	ui->recordButton->setText(tr("Nagrywaj"));
	ui->deviceComboBox->setEnabled(true);
	recordOnRun = false;
	disconnect(&recorder, 0, this, 0); // Prevent mainWindow from receiving signals from recorder.
}

void MainWindow::onCalibrationStopped()
{
	ui->deviceComboBox->setEnabled(true);
	ui->recordButton->setEnabled(true);
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
		auto user = User::GetUser(rowidx);
        if(User::GetUser(rowidx)->getShoutScore()!=0)userWindow->InsertUserToRanking(user, rowidx);
    }
    delete auw;
}

void MainWindow::on_actionExportToCsv_triggered()
{
	QString filename = QFileDialog::getSaveFileName(
				this, tr("Zapisz plik"), "", tr("Pliki CSV (*.csv);;Wszystkie pliki (*)"));
	if (filename == "")
		return;
	User::exportToCSV(filename);
}

void MainWindow::on_actionImportFromCsv_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, windowTitle(), tr("Zaimportowanie nowych danych spowoduje utratę wszystkich niezapisanych danych. Czy kontynuować?"),
                                   QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No)
    {
       return;
    }

	QFileDialog fdialog(this);
	QString filename;
	fdialog.setFileMode(QFileDialog::ExistingFile);
	QStringList filters;
	filters << tr("Plik CSV (*.csv)")
			<< tr("Wszystkie pliki (*)");
	fdialog.setNameFilters(filters);
	if (fdialog.exec())
	{
		filename = fdialog.selectedFiles().front();
	}
	else
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
	if (checked == false)
		return;
    userWindow->ShowAll();
    userWindow->SetShowing(m);
    userWindow->HideWomen();
}

void MainWindow::on_WomenRadioButton_toggled(bool checked)
{
	if (checked == false)
		return;
    userWindow->ShowAll();
    userWindow->SetShowing(w);
    userWindow->HideMen();
}

void MainWindow::on_AllRadioButton_toggled(bool checked)
{
	if (checked == false)
		return;
    userWindow->ShowAll();
    userWindow->SetShowing(a);
}

void MainWindow::on_actionCalibrate_triggered()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, tr("Kalibruj"), tr("Upewnij się, że z obecnie wybranego urządzenia do nagrywania można odebrać sygnał kalibracyjny i kontynuuj."),
								   QMessageBox::Ok|QMessageBox::Cancel);
	if (reply == QMessageBox::Cancel)
	{
	   return;
	}

	calibrator->Calibrate();
	ui->deviceComboBox->setEnabled(false);
	ui->recordButton->setEnabled(false);
}

void MainWindow::on_actionClose_triggered()
{
	QApplication::closeAllWindows();
}

void MainWindow::on_actionCalibrateFromFile_triggered()
{
	QFileDialog fdialog(this);
	QString filename;
	fdialog.setFileMode(QFileDialog::ExistingFile);
	QStringList filters;
	filters << tr("Plik WAV (*.wav)")
			<< tr("Wszystkie pliki (*)");
	fdialog.setNameFilters(filters);
	if (fdialog.exec())
	{
		filename = fdialog.selectedFiles().front();
	}
	else
		return;
	calibrator->CalibrateFromFile(filename);
}
