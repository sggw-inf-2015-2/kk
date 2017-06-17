#ifndef AUDIOMODEL_H
#define AUDIOMODEL_H

#include <QObject>
#include <QVector>
#include <complex>

using std::complex;

class AudioModel : public QObject
{
    Q_OBJECT
	static const int f = 48000;

	static QVector<complex<double> > fft(const QVector<complex<double>> &x);
	static double filterA(double frequency);
	explicit AudioModel(QObject *parent = 0) : QObject(parent) {}

public slots:
	static double computeLevel(const QVector<std::complex<double> > &x, double calibrationOffset = 0.0);
};

#endif // AUDIOMODEL_H
