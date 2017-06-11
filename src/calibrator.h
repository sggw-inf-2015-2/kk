#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <QObject>
#include <QVector>
#include <complex>
#include "recorder.h"
using namespace std;

class Calibrator : public QObject
{
    Q_OBJECT
public:
    explicit Calibrator(QObject *parent = nullptr);
    Calibrator(Recorder *Record);
    static void Calibrate();
    static Recorder *recorder;
signals:

public slots:
    void OnRecordingStopped( QVector<complex<double>> x );
};

#endif // CALIBRATOR_H
