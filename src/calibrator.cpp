#include "calibrator.h"
#include "audiomodel.h"

double Calibrator::calibrationData = 0.0;

Calibrator::Calibrator(Recorder *recorder, QObject *parent) : QObject(parent)
{
	this->recorder = recorder;
}

void Calibrator::Calibrate()
{
	connect(recorder, SIGNAL(recordingStopped(const QVector<std::complex<double> > &)), this, SLOT(OnRecordingStopped(const QVector<std::complex<double> > &)));
    recorder->Start();
}

void Calibrator::CalibrateFromFile(const QString &fileName)
{
    connect(recorder, SIGNAL(recordingStopped(const QVector<std::complex<double> > &)), this, SLOT(OnRecordingStopped(const QVector<std::complex<double> > &)));
    recorder->LoadAudioDataFromFile(fileName);
}

void Calibrator::OnRecordingStopped(const QVector<std::complex<double> > &x)
{
    disconnect(recorder, 0, this, 0);
	calibrationData = 94.0 - AudioModel::computeLevel(x);
	qDebug() << "Wartość kalibracji: " << calibrationData;
	emit calibrationStopped();
}
