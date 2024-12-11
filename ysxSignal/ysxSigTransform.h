#pragma once

#ifndef YSXSIGTRANSFORM_H
#define YSXSIGTRANSFORM_H

// #####################
// ####### By Sophia Cristina
// ####### Fourier transform or other types of transformations.
// #####################

// ####################################################################################
// ####################################################################################
// ####################################################################################

// ############################
// ####### FFT #######
// ############################

// COMPUTE THE FFT OF A VECTOR:
template <class T_>
std::vector<std::complex<double>> ysxSIG_FFT(std::vector<T_>& x)
{
    const size_t N = x.size();

    if (N == 1)
    {
        std::vector<std::complex<T_>> ret = {{x[0], 0}};
        return(ret);
    }

    // Divide into even and odd parts
    std::vector<double> x_even(N/2);
    std::vector<double> x_odd(N/2);

    for (size_t i = 0; i < N/2; ++i)
    {
        x_even[i] = x[2*i];
        x_odd[i] = x[2*i+1];
    }

    // Compute FFT of even and odd parts recursively
    std::vector<std::complex<double>> y_even = ysxSIG_FFT<double>(x_even);
    std::vector<std::complex<double>> y_odd = ysxSIG_FFT<double>(x_odd);

    // Combine the results
    std::vector<std::complex<double>> y(N);

    for (size_t k = 0; k < N/2; ++k)
    {
        std::complex<double> t = std::polar(1.0, -2 * PI * k / N) * y_odd[k];
        y[k] = y_even[k] + t;
        y[k + N/2] = y_even[k] - t;
    }

    return(y);
}
template <class T_>
std::vector<std::complex<double>> ysxSIG_FFT(T_* x, const uint32_t Size)
{
    const size_t N = Size;

    if (N == 1)
    {
        std::vector<std::complex<double>> ret = {{x[0], 0}};
        return(ret);
    }

    // Divide into even and odd parts
    std::vector<double> x_even(N/2);
    std::vector<double> x_odd(N/2);

    for (size_t i = 0; i < N/2; ++i)
    {
        x_even[i] = (double)x[2*i];
        x_odd[i] = (double)x[2*i+1];
    }

    // Compute FFT of even and odd parts recursively
    std::vector<std::complex<double>> y_even = ysxSIG_FFT<double>(&x_even[0], N/2);
    std::vector<std::complex<double>> y_odd = ysxSIG_FFT<double>(&x_odd[0], N/2);

    // Combine the results
    std::vector<std::complex<double>> y(N);

    for (size_t k = 0; k < N/2; ++k)
    {
        std::complex<double> t = std::polar(1.0, -2 * PI * k / N) * y_odd[k];
        y[k] = y_even[k] + t;
        y[k + N/2] = y_even[k] - t;
    }

    return(y);
}

// COMPUTE THE IFFT OF A COMPLEX VECTOR:
template <class T_>
std::vector<T_> ysxSIG_FFTi(std::vector<std::complex<T_>>& y)
{
    const size_t N = y.size();

    if (N == 1)
    {
	std::vector<T_> ret = { y[0].real() };
    	return(ret);
    }

    // Divide into even and odd parts
    std::vector<std::complex<T_>> y_even(N/2);
    std::vector<std::complex<T_>> y_odd(N/2);

    for (size_t i = 0; i < N/2; ++i)
    {
        y_even[i] = y[2*i];
        y_odd[i] = y[2*i+1];
    }

    // Compute iFFT of even and odd parts recursively
    std::vector<T_> x_even = ysxSIG_FFTi(y_even);
    std::vector<T_> x_odd = ysxSIG_FFTi(y_odd);

    // Combine the results
    std::vector<T_> x(N);

    for (size_t k = 0; k < N/2; ++k)
    {
        std::complex<T_> t = std::polar(1.0, 2 * PI * k / N) * x_odd[k];
        x[k] = x_even[k] + t.real();
        x[k + N/2] = x_even[k] - t.real();
    }

    // Normalize the results
    for (size_t i = 0; i < N; ++i) { x[i] /= N; }

    return(x);
}

#endif
