#include "dft.h"
#include "fft.h"
#include <iostream>
#include <fftw3.h>
using namespace std;

int main() {
    DFT dft;
    FFT fft;
    vector<complex<double>> input = { {0, 0}, {1, 0}, {0, 0}, {-1, 0} };
    vector<complex<double>> output_dft = dft.compute(input);
    vector<complex<double>> output_fft = fft.compute(input);

    int N = input.size();
    fftw_complex* fftw_input = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);

    fftw_complex* fftw_output = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);

    // Data preparation for FFTW3
    for (int i = 0; i < N; ++i) {
        fftw_input[i][0] = input[i].real();
        fftw_input[i][1] = input[i].imag();
    }

    // Create FFTW3 plan
    fftw_plan plan = fftw_plan_dft_1d(
        N,
        fftw_input,
        fftw_output,
        FFTW_FORWARD,
        FFTW_ESTIMATE
    );

    // Run FFTW3
    fftw_execute(plan);



    cout << "\nDFT Output:" << endl;
    for (const auto& val : output_dft) {
        cout << val << endl;
    }

    cout << "\nFFT Output:" << endl;
    for (const auto& val : output_fft) {
        cout << val << endl;
    }

    cout << "\nFFTW3 Output:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << "("
             << fftw_output[i][0]
             << ", "
             << fftw_output[i][1]
             << ")"
             << endl;
    }

    // Cleanup 
    fftw_destroy_plan(plan);
    fftw_free(fftw_input);
    fftw_free(fftw_output);

    return 0;
}