#include <functional>

#include "audiomodel.h"

const complex<double> AudioModel::ZERO = complex<double>(0, 0);

AudioModel::AudioModel(QObject *parent) : QObject(parent)
{

}

/**
 *  Returns the FFT of the specified complex array.
 *
 *  @param  x the complex array
 *  @return the FFT of the complex array <tt>x</tt>
 */
QVector<complex<double>> AudioModel::fft(QVector<complex<double> > x)
{
    int N = x.length();

    // base case
    if (N == 1) return QVector<complex<double>> { x[0] };

    // radix 2 Cooley-Tukey FFT
    if (N % 2 != 0) {
        throw invalid_argument("N is not a power of 2");
    }

    // fft of even terms
    QVector<complex<double>> even = QVector<complex<double>>(N/2);
    for (int k = 0; k < N/2; k++) {
        even[k] = x[2*k];
    }
    QVector<complex<double>> q = fft(even);

    // fft of odd terms
    QVector<complex<double>> odd  = even;  // reuse the array
    for (int k = 0; k < N/2; k++) {
        odd[k] = x[2*k + 1];
    }
    QVector<complex<double>> r = fft(odd);

    // combine
    QVector<complex<double>> y = QVector<complex<double>>(N);
    for (int k = 0; k < N/2; k++) {
        double kth = -2 * k * M_PI / N;
        complex<double> wk = complex<double>(cos(kth), sin(kth));
        y[k]       = q[k]+(wk * r[k]);
        y[k + N/2] = q[k]-(wk * r[k]);
    }
    return y;
}

/**
 *  Returns the inverse FFT of the specified complex array.
 *
 *  @param  x the complex array
 *  @return the inverse FFT of the complex array <tt>x</tt>
 */
QVector<complex<double>> AudioModel::ifft(QVector<complex<double> > x)
{
    int N = x.length();
    QVector<complex<double>> y = QVector<complex<double>>(N);

    // take conjugate
    for (int i = 0; i < N; i++) {
        y[i] = conj(x[i]);
    }

    // compute forward FFT
    y = fft(y);

    // take conjugate again
    for (int i = 0; i < N; i++) {
        y[i] = conj(y[i]);
    }

    // divide by N
    for (int i = 0; i < N; i++) {
        y[i] = y[i] * (1.0 / N);
    }

    return y;
}

/**
 *  Returns the linear convolution of the two specified complex arrays.
 *
 *  @param  x one complex array
 *  @param  y the other complex array
 *  @return the linear convolution of <tt>x</tt> and <tt>y</tt>
 */
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

/**
 *  Returns the circular convolution of the two specified complex arrays.
 *
 *  @param  x one complex array
 *  @param  y the other complex array
 *  @return the circular convolution of <tt>x</tt> and <tt>y</tt>
 */
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

/**
 *  This method calculates the signal power from the FFT.
 *
 *  @param x The FFT of the original signal,
 *  @param original_length The original length of the input data table.
 *
 *  @return The power of signal calculation by Parseval's theorem.
 */
double AudioModel::computeLevel(QVector<std::complex<double>> x, double calibrationOffset)
{
    int original_length = x.length();
    auto xfft = fft(x);
    transform(xfft.begin(), xfft.end(), xfft.begin(), [=](complex<double> z){ return z + calibrationOffset; });

    double result = 0;
    double fraction;
    for(auto z: xfft)
       result += abs(z) * abs(z);
    fraction = (double)xfft.length() / (double)original_length;
    result = result*fraction;
    return result;
}
