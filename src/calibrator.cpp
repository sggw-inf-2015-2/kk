#include "calibrator.h"
#include "recorder.h"
#include "audiomodel.h"

Calibrator::Calibrator(QObject *parent) : QObject(parent)
{

}
void Calibrator::Calibrate(QVector<complex<double>> x)
{
    Recorder Calibration;
    Calibration.Start();
    AudioModel::CalibrationData = AudioModel::ComputeLevel(x);
    Calibration.Stop();//fafafasd
}
