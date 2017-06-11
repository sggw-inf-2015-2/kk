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
    void Calibrate(QVector<complex<double>> x);
signals:

public slots:
};

#endif // CALIBRATOR_H
