#pragma once
#include "fourier-transform.h"
#include <iostream>
#include <valarray>

class FFT : public FourierTransform {
public:
    std::vector<std::complex<double>> compute(const std::vector<std::complex<double>>& input) override;
    std::vector<std::complex<double>> computeInverse(const std::vector<std::complex<double>>& input) override;
private:
    void fft_recursive(std::vector<std::complex<double>>& input);
    void ifft_recursive(std::vector<std::complex<double>>& input);    
};