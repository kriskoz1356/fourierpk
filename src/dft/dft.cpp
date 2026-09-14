#include "dft.h"
using namespace std;

vector<complex<double>> DFT::compute(const vector<double>& input) {
    int N = input.size();
    vector<complex<double>> output(N);

    for(int k = 0; k < N; k++) {
        double realSum = 0.0;
        double imagSum = 0.0;
        for(int n = 0; n < N; n++) {
            double angle = 2 * PI * k * n / N;
            realSum += input[n] * cos(angle);
            imagSum += input[n] * sin(angle);
        }
        if(abs(realSum) < EPS) realSum = 0.0;
        if(abs(imagSum) < EPS) imagSum = 0.0;
        output[k] = complex<double>(realSum, imagSum);
    }
    return output;
}

vector<double> DFT::computeInverse(const vector<complex<double>>& input) {

    int N = input.size();
    vector<double> output(N);

    for(int n = 0; n < N; n++) {
        double realSum = 0.0;
        for(int k = 0; k < N; k++) {
            double angle = 2 * PI * k * n / N;
            realSum += input[k].real() * cos(angle) - input[k].imag() * sin(angle);
        }
        if(abs(realSum) < EPS) realSum = 0.0;
        output[n] = realSum / N;
    }
    return output;
}