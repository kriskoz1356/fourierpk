#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <complex>

class FileIO {
public:
    // Reads a signal from a text file into a vector
    std::vector<double> readSignal(const std::string& fileName);
    // Writes a signal to a text file from a vector
    void writeSignal(const std::vector<double>& signal, const std::string& fileName);

    // Reads a spectrum from a text file into a vector of complex numbers
    std::vector<std::complex<double>> readSpectrum(const std::string& fileName);
    // Writes a spectrum to a text file from a vector of complex numbers
    void writeSpectrum(const std::vector<std::complex<double>>& spectrum, const std::string& fileName);
};