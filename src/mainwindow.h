#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "recorder.h"
#include "user.h"
#include "adduserwindow.h"
#include "userwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(UserWindow *uw, QWidget *parent = 0);
    static Recorder* GetRecorder();
    ~MainWindow();
	void closeEvent(QCloseEvent *event) override;

private slots:
    void proceed();
	void onRecordingStopped(const QVector<std::complex<double> > &complexData);
    void on_AddUserButton_clicked();
    void on_EditUserButton_clicked();
    void on_MenRadioButton_toggled(bool checked);
    void on_WomenRadioButton_toggled(bool checked);
    void on_AllRadioButton_toggled(bool checked);
	void on_actionExportToCsv_triggered();
	void on_actionImportFromCsv_triggered();
	void on_actionCalibrate_triggered();
	void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;
    UserWindow *userWindow;
    bool recordOnRun;
    Recorder recorder;
    AddUserWindow *auw;
	int currentUser;

    void initialiseDeviceList();
    void insertUserToList(User * const user);
};

#endif // MAINWINDOW_H
