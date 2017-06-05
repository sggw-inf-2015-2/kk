#include "audiomodel.h"

const complex<double> AudioModel::ZERO = complex<double>(0, 0);

AudioModel::AudioModel(QObject *parent) : QObject(parent)
{

}

QVector<complex<double>> AudioModel::fft(QVector<complex<double> > x)
{
    return QVector<complex<double>>();
}

QVector<complex<double>> AudioModel::ifft(QVector<complex<double> > x)
{
    return QVector<complex<double>>();
}

QVector<complex<double>> AudioModel::convolve(QVector<std::complex<double> > x, QVector<std::complex<double> > y)
{
    QVector<complex<double>> a = QVector<complex<double>>(2*x.length());
    for (int i = 0; i < x.length(); i++)
        a[i] = x[i];
    for (int i = x.length(); i < 2*x.length(); i++)
        a[i] = ZERO;

    QVector<complex<double>> b = QVector<complex<double>>(2*y.length());
    for (int i = 0; i < y.length(); i++)
        b[i] = y[i];
    for (int i = y.length(); i < 2*y.length(); i++)
        b[i] = ZERO;

    return cconvolve(a, b);
}

QVector<complex<double>> AudioModel::cconvolve(QVector<std::complex<double> > x, QVector<std::complex<double> > y)
{
    // TODO: should probably pad x and y with 0s so that they have same length
    // and are powers of 2
    if (x.length() != y.length()) {
       // throw new IllegalArgumentException("Dimensions don't agree");
    }

    int N = x.length();

    // compute FFT of each sequence
    QVector<complex<double>> a = fft(x);
    QVector<complex<double>> b = fft(y);

    // point-wise multiply
    QVector<complex<double>> c = QVector<complex<double>>(N);
    for (int i = 0; i < N; i++) {
        c[i] = a[i] * b[i];
    }

    // compute inverse FFT
    return ifft(c);
}
