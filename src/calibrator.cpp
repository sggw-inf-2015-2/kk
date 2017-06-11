#include "calibrator.h"
#include "recorder.h"
#include "audiomodel.h"
#include "mainwindow.h"
Calibrator::Calibrator(QObject *parent) : QObject(parent)
{

}
Calibrator::Calibrator(Recorder *record)
{
    Calibrator::recorder = record;
}
void Calibrator::Calibrate()
{
    Recorder *Calibration = recorder;
    Calibration->Start();
}

void OnRecordingStopped( QVector<complex<double>> x )
{
    AudioModel::CalibrationData = AudioModel::ComputeLevel(x);
}
