#pragma once
#include "dft.h"
#include "fft.h"
#include "fftw.h"
#include "file-io.h"
#include <vector>
#include <complex>
#include <iostream>
#include <chrono>
#include <iomanip>
using namespace std::chrono;

class Benchmark {
private:
    FileIO fileIO;
    const std::vector<double> signal512 = fileIO.readSignal("data/signal512.txt");
    const std::vector<double> signal4096 = fileIO.readSignal("data/signal4096.txt");
    const std::vector<double> signal8192 = fileIO.readSignal("data/signal8192.txt");
    const std::vector<std::vector<double>> signals = { signal512, signal4096, signal8192 };
    const std::vector<std::complex<double>> spectrum512 = fileIO.readSpectrum("data/spectrum512.txt");
    const std::vector<std::complex<double>> spectrum4096 = fileIO.readSpectrum("data/spectrum4096.txt");
    const std::vector<std::complex<double>> spectrum8192 = fileIO.readSpectrum("data/spectrum8192.txt");
    const std::vector<std::vector<std::complex<double>>> spectra = { spectrum512, spectrum4096, spectrum8192 };

    double calculateAverage(const std::vector<int>& times) {
        int sum = 0;
        for (int time : times) {
            sum += time;
        }
        return static_cast<double>(sum) / times.size() / 1000.0; // Convert to milliseconds
    }
public:
    void runBenchmark();
    void runCustomBenchmark(const std::string& fileName, const char& operation, const int& repetitions);
};