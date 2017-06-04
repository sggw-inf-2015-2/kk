#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "recorder.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void proceed();
	void onRecordingStopped(qint64 bytes);

private:
    Ui::MainWindow *ui;
    bool recordOnRun;
    Recorder recorder;

    void initialiseDeviceList();
};

#endif // MAINWINDOW_H
