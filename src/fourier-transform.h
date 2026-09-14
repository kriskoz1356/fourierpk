#pragma once
#include <iostream>
#include <vector>
#include <complex>

class FourierTransform {
protected:
    const double PI = 3.141592653589793238464243383279;
    const double EPS = 1e-12;
public:
    virtual std::vector<std::complex<double>> compute(const std::vector<double>& input) = 0;
    virtual std::vector<double> computeInverse(const std::vector<std::complex<double>>& input) = 0;
    virtual ~FourierTransform() = default;
};