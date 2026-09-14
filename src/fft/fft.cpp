#include "fft.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>
using namespace std;

bool is_power_of_two(int n) {
    if (n <= 0) {
        return false;
    }
    else{
        int logValue = log2(n);
        return (pow(2, logValue) == n);
    }
}

void FFT::fft_recursive(vector<complex<double>>& input) {
    int N = input.size();
    if (N <= 1) return;

    vector<complex<double>> even(N / 2);
    vector<complex<double>> odd(N / 2);
    for(int i = 0; i < N / 2; i++) {
        even[i] = input[2 * i];
        odd[i] = input[2 * i + 1];
    }
    fft_recursive(even);
    fft_recursive(odd);

    for(int k = 0; k< N / 2; k++){
        complex<double>t = polar(1.0, -2 * PI * k / N) * odd[k];
        input[k] = even[k] + t;
        input[k + N / 2] = even[k] - t;
    }
}

vector<complex<double>> FFT::compute(const vector<complex<double>>& input) {
    if (!is_power_of_two(input.size())) {
        throw invalid_argument("FFT Error: Input size must be a power of two.");
    }
    vector<complex<double>> output = input;
    fft_recursive(output);

    for_each(output.begin(), output.end(), [this](complex<double>& temp){
        if(abs(temp.real()) < EPS) temp.real(0);
        if(abs(temp.imag()) < EPS) temp.imag(0);
    });
    return output;
}

void FFT::ifft_recursive(vector<complex<double>>& input) {
    for (int i = 0; i < input.size(); i++) {
        input[i] = conj(input[i]);
    }

    fft_recursive(input);

    for (int i = 0; i < input.size(); i++) {
        input[i] = conj(input[i]);
    }

    for (int i = 0; i < input.size(); i++) {
        input[i] /= input.size();
    }
}

vector<complex<double>> FFT::computeInverse(const vector<complex<double>>& input) {
    if (!is_power_of_two(input.size())) {
        throw invalid_argument("FFT Error: Input size must be a power of two.");
    }
    vector<complex<double>> output = input;
    ifft_recursive(output);

    for_each(output.begin(), output.end(), [this](complex<double>& temp){
        if(abs(temp.real()) < EPS) temp.real(0);
        if(abs(temp.imag()) < EPS) temp.imag(0);
    });
    return output;
}