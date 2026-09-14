#include "fftw.h"
using namespace std;

vector<complex<double>> FFTW::compute(const vector<double>& input) {
    int N = input.size();

    // Allocate memory for FFTW input and output
    fftw_complex* fftw_input = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex* fftw_output = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);

    // Prepare data for FFTW
    for (int i = 0; i < N; ++i) {
        fftw_input[i][0] = input[i];
        fftw_input[i][1] = 0.0;
    }

    // Create FFTW plan
    fftw_plan plan = fftw_plan_dft_1d(N, fftw_input, fftw_output, FFTW_FORWARD, FFTW_ESTIMATE);

    // Execute the plan
    fftw_execute(plan);

    // Store the output in a vector of complex numbers
    vector<complex<double>> output(N);
    for (int i = 0; i < N; ++i) {
        output[i] = complex<double>(fftw_output[i][0], fftw_output[i][1]);
    }

    // Clean up
    fftw_destroy_plan(plan);
    fftw_free(fftw_input);
    fftw_free(fftw_output);

    return output;
}

vector<double> FFTW::computeInverse(const vector<complex<double>>& input) {
    int N = input.size();

    // Allocate memory for FFTW input and output
    fftw_complex* fftw_input = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex* fftw_output = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);

    // Prepare data for FFTW
    for (int i = 0; i < N; ++i) {
        fftw_input[i][0] = input[i].real();
        fftw_input[i][1] = input[i].imag();
    }

    // Create FFTW plan for inverse transform
    fftw_plan plan = fftw_plan_dft_1d(N, fftw_input, fftw_output, FFTW_BACKWARD, FFTW_ESTIMATE);

    // Execute the plan
    fftw_execute(plan);

    // Store the output in a vector of complex numbers and normalize
    vector<double> output(N);
    for (int i = 0; i < N; ++i) {
        output[i] = fftw_output[i][0] / N;
    }

    // Cleanup
    fftw_destroy_plan(plan);
    fftw_free(fftw_input);
    fftw_free(fftw_output);

    return output;
}