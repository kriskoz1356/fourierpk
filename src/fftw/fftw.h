#pragma once
#include "fourier-transform.h"
#include <fftw3.h>
class FFTW : public FourierTransform {
public:
    std::vector<std::complex<double>> compute(const std::vector<double>& input) override;
    std::vector<double> computeInverse(const std::vector<std::complex<double>>& input) override;
};