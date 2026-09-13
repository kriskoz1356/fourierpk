#include "dft.h"
using namespace std;

vector<complex<double>> DFT::compute(const vector<complex<double>>& input) {
    int N = input.size();
    vector<complex<double>> output(N);

    for(int k = 0; k < N; k++) {
        double realSum = 0.0;
        double imagSum = 0.0;
        for(int n = 0; n < N; n++) {
            double angle = 2 * PI * k * n / N;
            realSum += input[n].real() * cos(angle) + input[n].imag() * sin(angle);
            imagSum += input[n].imag() * cos(angle) - input[n].real() * sin(angle);
        }
        if(abs(realSum) < EPS) realSum = 0.0;
        if(abs(imagSum) < EPS) imagSum = 0.0;
        output[k] = complex<double>(realSum, imagSum);
    }
    return output;
}

vector<complex<double>> DFT::computeInverse(const vector<complex<double>>& input) {
    int N = input.size();
    vector<complex<double>> output(N);

    for(int n = 0; n < N; n++) {
        double realSum = 0.0;
        double imagSum = 0.0;
        for(int k = 0; k < N; k++) {
            double angle = 2 * PI * k * n / N;
            realSum += input[k].real() * cos(angle) - input[k].imag() * sin(angle);
            imagSum += input[k].real() * sin(angle) + input[k].imag() * cos(angle);
        }
        if(abs(realSum) < EPS) realSum = 0.0;
        if(abs(imagSum) < EPS) imagSum = 0.0;
        output[n] = complex<double>(realSum / N, imagSum / N);
    }
    return output;
}