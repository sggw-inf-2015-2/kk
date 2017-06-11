#include "calibrator.h"
#include "audiomodel.h"

Calibrator::Calibrator(Recorder *recorder, QObject *parent) : QObject(parent)
{
	this->recorder = recorder;
}

void Calibrator::Calibrate()
{
	connect(recorder, SIGNAL(recordingStopped(const QVector<std::complex<double> > &)), this, SLOT(OnRecordingStopped(const QVector<std::complex<double> > &)));
	recorder->Start();
}

void Calibrator::OnRecordingStopped(const QVector<std::complex<double> > &x)
{
	disconnect(recorder, 0, this, 0);
	AudioModel::CalibrationData = AudioModel::computeLevel(x);
	emit calibrationStopped();
}
