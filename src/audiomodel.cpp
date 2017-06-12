#define _USE_MATH_DEFINES

#include <functional>
#include <cstdlib>
#include <fftw3.h>

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

    fftw_complex *in, *out;
    fftw_plan p;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    for (int i = 0; i < N; i++) {
        in[i][0] = x[i].real();
        in[i][1] = x[i].imag();
    }

    fftw_execute(p);

    auto y = QVector<complex<double>>(N);
    for (int i = 0; i < N; i++) {
        y[i] = complex<double>(out[i][0], out[i][1]);
    }

    fftw_destroy_plan(p);
    fftw_free(in);
    fftw_free(out);
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
       throw new invalid_argument("Dimensions don't agree.");
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
double AudioModel::computeLevel(QVector<std::complex<double>> x, double calibrationOffset, double referencePower)
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

    return log10(result / referencePower);
}
