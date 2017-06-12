#ifndef AUDIOMODEL_H
#define AUDIOMODEL_H

#include <QObject>
#include <QVector>
#include <complex>

using namespace std;

class AudioModel : public QObject
{
    Q_OBJECT

    static const complex<double> ZERO;

    static QVector<complex<double>> convolve(QVector<complex<double>> zs, QVector<complex<double>> qs);
    static QVector<complex<double>> cconvolve(QVector<complex<double>> zs, QVector<complex<double>> qs);

    static QVector<complex<double>> fft(QVector<complex<double>> x);
    static QVector<complex<double>> ifft(QVector<complex<double>> x);

    explicit AudioModel(QObject *parent = 0);

public slots:
    static double computeLevel(QVector<std::complex<double>> x, double calibrationOffset = 0.0, double referencePower = 1.0);
};

#endif // AUDIOMODEL_H
