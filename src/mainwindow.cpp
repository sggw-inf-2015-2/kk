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
