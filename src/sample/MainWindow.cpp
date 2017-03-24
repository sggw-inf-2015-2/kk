#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    recordOnRun = false;
    connect(ui->recordButton, SIGNAL(pressed()), this, SLOT(proceed()));
	connect(&recorder, SIGNAL(bytesSaved(int)), this, SLOT(printBytes(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::proceed()
{
    if (!recordOnRun)
    {
        recorder.Start();
        recordOnRun = true;
		ui->recordButton->setText(tr("Zatrzymaj"));
    }
    else
    {
        recorder.Stop();
        recordOnRun = false;
		ui->recordButton->setText(tr("Nagrywaj"));
		ui->bytes->setText(tr("0 bajtów"));
	}
}

void MainWindow::printBytes(int bytes)
{
	ui->bytes->setText(QString::number(bytes) + " bajtów");
}
