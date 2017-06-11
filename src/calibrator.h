#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <QObject>
#include <QVector>
#include "recorder.h"

class Calibrator : public QObject
{
    Q_OBJECT
	Recorder *recorder;
public:
	explicit Calibrator(Recorder *recorder, QObject *parent = nullptr);
	void Calibrate();
signals:
	void calibrationStopped();

public slots:
	void OnRecordingStopped(const QVector<std::complex<double> > &x);
};

#endif // CALIBRATOR_H
