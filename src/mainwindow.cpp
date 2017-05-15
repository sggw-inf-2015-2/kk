#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    recordOnRun = false;
    connect(ui->recordButton, SIGNAL(clicked()), this, SLOT(proceed()));
	connect(&recorder, SIGNAL(bytesSaved(qint64)), this, SLOT(showSize(qint64)));
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
          //  ui->recordButton->setText(tr("Zatrzymaj"));
            ui->bytes->clear();
		}
		else
        {
            //recorder.Stop();
            recordOnRun = false;
            //ui->recordButton->setText(tr("Nagrywaj"));
		}
	}
	catch (exception &e)
	{
		QMessageBox::critical(this, windowTitle(), e.what());
		return;
	}
}

void MainWindow::showSize(qint64 size)
{
	ui->bytes->setText(QString::number((long)size) + " bajtów");
}
