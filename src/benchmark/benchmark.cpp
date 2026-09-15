#include "benchmark.h"
#include <numeric>
using namespace std;

namespace{
    int repetitions = 5;
    const vector<int> sizes = { 512, 4096, 8192 };

    template<typename Func>
    long long measureTime(Func operation) {
        auto start = high_resolution_clock::now();
        operation();
        auto stop = high_resolution_clock::now();
        return duration_cast<microseconds>(stop - start).count();
    }

    double averageTime(const vector<int>& times) {
        if (times.empty()) return 0.0;
        long long sum = std::accumulate(times.begin(), times.end(), 0LL);
        return static_cast<double>(sum) / times.size() / 1000.0; // Convert to milliseconds
    }

    void printTable(const string& title,
                    const vector<vector<int>>& timesMethod1, const string& name1,
                    const vector<vector<int>>& timesMethod2, const string& name2,
                    const vector<vector<int>>& timesMethod3, const string& name3,
                    const vector<int>& sizes) {
        cout << "------------(" << title << ")------------" << endl;
        cout << "-------------------(Time in ms)------------------" << endl;
        cout << endl;
        cout << left << setw(12) << " " << setw(12) << " " << setw(12) << "Size" << setw(12) << " " << endl;
        cout << left << setw(12) << "Method";
        for (int size : sizes) {
            cout << setw(12) << size;
        }
        cout << endl;
        cout << "------------------------------------------------" << endl;
        cout << fixed << setprecision(4);

        auto printRow = [&](const string& name, const vector<vector<int>>& times) {
            cout << setw(12) << name;
            for (size_t i = 0; i < sizes.size(); i++) {
                cout << setw(12) << averageTime(times[i]);
            }
            cout << endl;
        };

        printRow(name1, timesMethod1);
        printRow(name2, timesMethod2);
        printRow(name3, timesMethod3);
    }

    void printCustomResult(const string& methodName, const vector<int>& times) {
        double avgTime = averageTime(times);
        cout << methodName << ": " << avgTime << " ms" << endl;
    }
}

void Benchmark::runBenchmark() {
    DFT dft;
    FFT fft;
    FFTW fftw;

    const int numSizes = sizes.size();

    vector<vector<int>> timesDFT(numSizes);
    vector<vector<int>> timesFFT(numSizes);
    vector<vector<int>> timesFFTW(numSizes);

    vector<vector<int>> timesIDFT(numSizes);
    vector<vector<int>> timesIFFT(numSizes);
    vector<vector<int>> timesIFFTW(numSizes);

    for (size_t i = 0; i < signals.size(); i++) {
        for (int j = 0; j < repetitions; j++) {
            timesDFT[i].push_back(measureTime([&] { dft.compute(signals[i]); }));
            timesFFT[i].push_back(measureTime([&] { fft.compute(signals[i]); }));
            timesFFTW[i].push_back(measureTime([&] { fftw.compute(signals[i]); }));

            timesIDFT[i].push_back(measureTime([&] { dft.computeInverse(spectra[i]); }));
            timesIFFT[i].push_back(measureTime([&] { fft.computeInverse(spectra[i]); }));
            timesIFFTW[i].push_back(measureTime([&] { fftw.computeInverse(spectra[i]); }));
        }
    }

    printTable("Fourier Transform",
               timesDFT, "DFT",
               timesFFT, "FFT",
               timesFFTW, "FFTW",
               sizes);

    cout << endl << endl;

    printTable("Inverse Fourier Transform",
               timesIDFT, "DFT",
               timesIFFT, "FFT",
               timesIFFTW, "FFTW",
               sizes);
}

void Benchmark::runCustomBenchmark(const std::string& fileName, const char& operation, const int& repetitions) {
    if (repetitions <= 0) {
        throw std::invalid_argument("Repetitions must be a positive integer!");
    }

    DFT dft;
    FFT fft;
    FFTW fftw;

    vector<double> signal = fileIO.readSignal(fileName);
    vector<std::complex<double>> spectrum = fileIO.readSpectrum(fileName);

    vector<int> timesDFT;
    vector<int> timesFFT;
    vector<int> timesFFTW;

    if (operation == 'f') { // Forward transform
        for (int i = 0; i < repetitions; i++) {
            timesDFT.push_back(measureTime([&] { dft.compute(signal); }));
            timesFFT.push_back(measureTime([&] { fft.compute(signal); }));
            timesFFTW.push_back(measureTime([&] { fftw.compute(signal); }));
        }
        printCustomResult("DFT", timesDFT);
        printCustomResult("FFT", timesFFT);
        printCustomResult("FFTW", timesFFTW);
    } else if (operation == 'i') { // Inverse transform
        for (int i = 0; i < repetitions; i++) {
            timesDFT.push_back(measureTime([&] { dft.computeInverse(spectrum); }));
            timesFFT.push_back(measureTime([&] { fft.computeInverse(spectrum); }));
            timesFFTW.push_back(measureTime([&] { fftw.computeInverse(spectrum); }));
        }
        printCustomResult("IDFT", timesDFT);
        printCustomResult("IFFT", timesFFT);
        printCustomResult("IFFTW", timesFFTW);
    } else {
        throw std::invalid_argument("Invalid operation! Use 'f' for forward or 'i' for inverse.");
    }
}