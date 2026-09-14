#include "file-io.h"
using namespace std;

// *********************************************************************************
// Signal
// *********************************************************************************

// Method for reading a signal from a file and writing it to a vector of type double
vector<double> FileIO::readSignal(const string& fileName) {
    vector<double> signal; // Create a vector to store the signal

    // Read from file
    ifstream file(fileName);
    
    // Exception (file opening error)
    if (!file.is_open()) {
        throw(runtime_error("Error opening file for reading: " + fileName));
    }
    double value; // Variable to store the value read from the file
    
    // Read data into the vector
    while (file >> value) {
        signal.push_back(value);
    }
    
    // Exception (incorrect data)
    if (!file.eof()) {
        throw(runtime_error("Incorrect data in file " + fileName));
    }
    
    // Exception (empty file)
    if(signal.empty()) {    
        throw(runtime_error("The provided signal " + fileName + " is empty!"));
    }

    file.close(); // Close the file
    return signal; // Return the vector
}

void FileIO::writeSignal(const vector<double>& signal, const string& fileName) {
    ofstream file(fileName); // Open the file for writing

    // Exception (file opening error)
    if (!file.is_open()) {
        throw(runtime_error("Error opening file for writing: " + fileName));
    }
    else {
        // Write to the file
        for (int i = 0; i < signal.size(); i++) {
            file << signal[i] << " ";
        }
        file.close(); // Close the file
    }
}

// *********************************************************************************
// Spectrum
// *********************************************************************************

// Method for reading a spectrum from a file and writing it to a vector of type complex<double>
vector<complex<double>> FileIO::readSpectrum(const string& fileName) {
    vector<complex<double>> spectrum; // Create a vector to store the spectrum

    // Read from file
    ifstream file(fileName);
    
    // Exception (file opening error)
    if (!file.is_open()) {
        throw(runtime_error("Error opening file for reading: " + fileName));
    }
    double realPart, imaginaryPart; // Variables to store the real and imaginary parts read from the file
    
    // Read data into the vector
    while (file >> realPart >> imaginaryPart) {
        spectrum.push_back(complex<double>(realPart, imaginaryPart));
    }
    
    // Exception (incorrect data)
    if (!file.eof()) {
        throw(runtime_error("Incorrect data in file " + fileName));
    }
    
    // Exception (empty file)
    if(spectrum.empty()) {    
        throw(runtime_error("The provided spectrum " + fileName + " is empty!"));
    }

    file.close(); // Close the file
    return spectrum; // Return the vector
}

void FileIO::writeSpectrum(const vector<complex<double>>& spectrum, const string& fileName) {
    ofstream file(fileName); // Open the file for writing

    // Exception (file opening error)
    if (!file.is_open()) {
        throw(runtime_error("Error opening file for writing: " + fileName));
    }
    else {
        // Write to the file
        for (int i = 0; i < spectrum.size(); i++) {
            file << spectrum[i].real() << " " << spectrum[i].imag() << endl;
        }
        file.close(); // Close the file
    }
}