#pragma once
#include "fourier-transform.h"

class FFT : public FourierTransform {
public:
    std::vector<std::complex<double>> compute(const std::vector<double>& input) override;
    std::vector<double> computeInverse(const std::vector<std::complex<double>>& input) override;
private:
    void fft_recursive(std::vector<std::complex<double>>& input);
    void ifft_recursive(std::vector<std::complex<double>>& input);    
};