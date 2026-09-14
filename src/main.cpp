#include "dft.h"
#include "fft.h"
#include "fftw.h"
#include "file-io.h"
#include <iostream>
using namespace std;

int main() {
    FileIO fileIO;
    DFT dft;
    FFT fft;
    FFTW fftw;
    vector<double> signal = fileIO.readSignal("data/signal.txt");
    vector<complex<double>> spectrum = fileIO.readSpectrum("data/spectre.txt");

    // Compute the DFT, FFT, and FFTW of the signal
    vector<complex<double>> dft_output = dft.compute(signal);
    vector<complex<double>> fft_output = fft.compute(signal);
    vector<complex<double>> fftw_output = fftw.compute(signal);

    // Compute the inverse DFT, FFT, and FFTW of the spectrum
    vector<double> dft_inverse_output = dft.computeInverse(spectrum);
    vector<double> fft_inverse_output = fft.computeInverse(spectrum);
    vector<double> fftw_inverse_output = fftw.computeInverse(spectrum);

    // Write the outputs to files
    fileIO.writeSpectrum(dft_output, "data/output/dft_output.txt");
    fileIO.writeSpectrum(fft_output, "data/output/fft_output.txt");
    fileIO.writeSpectrum(fftw_output, "data/output/fftw_output.txt");
    fileIO.writeSignal(dft_inverse_output, "data/output/dft_inverse_output.txt");
    fileIO.writeSignal(fft_inverse_output, "data/output/fft_inverse_output.txt");
    fileIO.writeSignal(fftw_inverse_output, "data/output/fftw_inverse_output.txt");

    return 0;
}