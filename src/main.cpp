#include "dft.h"
#include "fft.h"
#include "fftw.h"
#include <iostream>
using namespace std;

int main() {
    DFT dft;
    FFT fft;
    FFTW fftw;

    vector<complex<double>> input = { {0, 0}, {1, 0}, {0, 0}, {-1, 0} };
    vector<complex<double>> input2 = { {0, 0}, {0, -2}, {0, 0}, {0, 2} };
    vector<complex<double>> output_dft = dft.compute(input);
    vector<complex<double>> output_fft = fft.compute(input);
    vector<complex<double>> output_fftw = fftw.computeInverse(input2);

    cout << "\nDFT Output:" << endl;
    for (const auto& val : output_dft) {
        cout << val << endl;
    }

    cout << "\nFFT Output:" << endl;
    for (const auto& val : output_fft) {
        cout << val << endl;
    }

    cout << "\nFFTW Output:" << endl;
    for (const auto& val : output_fftw) {
        cout << val << endl;
    }

    return 0;
}