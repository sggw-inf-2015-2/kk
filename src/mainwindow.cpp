#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    recordOnRun = false;
    connect(ui->recordButton, SIGNAL(pressed()), this, SLOT(proceed()));
	connect(&recorder, SIGNAL(recordingStopped(qint64)), this, SLOT(onRecordingStopped(qint64)));
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
