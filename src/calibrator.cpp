#include "calibrator.h"
#include "recorder.h"
#include "audiomodel.h"
#include "mainwindow.h"
Calibrator::Calibrator(QObject *parent) : QObject(parent)
{

}
void Calibrator::Calibrate()
{
    Recorder *Calibration = MainWindow::GetRecorder();
    Calibration->Start();
}

void OnRecordingStopped( QVector<complex<double>> x )
{
    AudioModel::CalibrationData = AudioModel::ComputeLevel(x);
}
