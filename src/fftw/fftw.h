#pragma once
#include "fourier-transform.h"
#include <fftw3.h>
#include <iostream>
#include <vector>
#include <complex>

class FFTW : public FourierTransform {
public:
    std::vector<std::complex<double>> compute(const std::vector<std::complex<double>>& input) override;
    std::vector<std::complex<double>> computeInverse(const std::vector<std::complex<double>>& input) override;
};