#include "dft.h"
#include "fft.h"
#include <iostream>
using namespace std;

int main() {
    DFT dft;
    FFT fft;
    vector<complex<double>> input = { {0, 0}, {1, 0}, {0, 0}, {-1, 0} };
    vector<complex<double>> output_dft = dft.compute(input);
    vector<complex<double>> output_fft = fft.compute(input);

    cout << "DFT Output:" << endl;
    for (const auto& val : output_dft) {
        cout << val << endl;
    }

    cout << "FFT Output:" << endl;
    for (const auto& val : output_fft) {
        cout << val << endl;
    }

    return 0;
}