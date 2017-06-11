#ifndef CALIBRATOR_H
#define CALIBRATOR_H

#include <QObject>
#include <QVector>
#include <complex>

using namespace std;

class Calibrator : public QObject
{
    Q_OBJECT
public:
    explicit Calibrator(QObject *parent = nullptr);
    void Calibrate();
signals:

public slots:
    void OnRecordingStopped( QVector<complex<double>> x );
};

#endif // CALIBRATOR_H
