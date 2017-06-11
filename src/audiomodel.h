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
public:
    explicit AudioModel(QObject *parent = 0);

    QVector<complex<double>> convolve(QVector<complex<double>> zs, QVector<complex<double>> qs);
    QVector<complex<double>> cconvolve(QVector<complex<double>> zs, QVector<complex<double>> qs);

    QVector<complex<double>> fft(QVector<complex<double>> x);
    QVector<complex<double>> ifft(QVector<complex<double>> x);

    double computeLevel(QVector<complex<double>> x, int original_length);
signals:

public slots:
};

#endif // AUDIOMODEL_H
