#include "benchmark.h"
#include <iostream>
using namespace std;

void instruction() {
    cout << "==================================================(INSTRUCTION)==================================================" << endl;
    cout << "The program is run using flags:" << endl;
    cout << "-m -> mode of operation" << endl;
    cout << "-in -> input file" << endl;
    cout << "-out -> output file" << endl;
    cout << "-r -> number of repetitions" << endl;
    cout << "-fi -> short for transform forward/inverse" << endl;
    cout << endl;
    cout << "The program has 3 modes of operation: auto, custom, and [dft|fft]" << endl;
    cout << "The auto mode performs automatic timing measurements of various Fourier transform methods (inverse)" << endl;
    cout << "The custom mode takes an input file, number of repetitions, and a decision (transform/inverse) from the user" << endl;
    cout << "The dft/fft modes take an input file, output file, and a decision (transform/inverse) from the user" << endl;
    cout << "Each mode has a specific number of arguments required for execution!" << endl;
    cout << endl;
    cout << "Example usage of the program:" << endl;
    cout << "./Fourier.exe -m auto" << endl;
    cout << "./Fourier.exe -m custom -in signal.txt -fi f -r 9 -> will time test Fourier transform methods 9 times" << endl;
    cout << "./Fourier.exe -m dft -in signal.txt -fi f -out spectrumDFT.txt -> will perform Fourier transform using DFT method" << endl;
    cout << "on data from signal.txt and save to spectrumDFT.txt" << endl;
    cout << "./Fourier.exe -m fft -in spectrum.txt -fi i -out reconstructedSignal.txt -> will perform inverse Fourier transform" << endl;
    cout << "using FFT method on data from spectrum.txt and save to reconstructedSignal.txt" << endl;
    cout << "==================================================================================================================" << endl;
}

void missingArgument() {
    cout << "Missing argument after flag!" << endl;
    instruction();
}

int main(int argc, char* argv[]) {
	try {
		Benchmark benchmark;

		// Check for the correct number of arguments
		if (argc < 3) {
			instruction();
			return 0;
		}

		// Variables for command line argument parsing
		string mode;
		string inputFile, outputFile;
		char transformMode = 0;
		int repetitions = 0;

		// Loop to parse command line arguments based on flags
		for (int i = 1; i < argc; i++) {
			string arg = argv[i];
			if (arg == "-m") {
				if (i + 1 >= argc) {
					missingArgument();
					return 0;
				}
				else {
					mode = argv[++i];
				}
			}
			else if (arg == "-in") {
				if (i + 1 >= argc) {
					missingArgument();
					return 0;
				}
				else {
					inputFile = argv[++i];
				}
			}
			else if (arg == "-out") {
				if (i + 1 >= argc) {
					missingArgument();
					return 0;
				}
				else {
					outputFile = argv[++i];
				}
			}
			else if (arg == "-r") {
				if (i + 1 >= argc) {
					missingArgument();
					return 0;
				}
				else {
					try {
						repetitions = stoi(argv[++i]);
						if (repetitions <= 0) {
							throw(invalid_argument("Number of repetitions must be a positive integer!"));
						}
					}
					catch (const exception& error) {
						cout << error.what() << endl;
						instruction();
						return 0;
					}
				}
			}
			else if (arg == "-fi") {
				if (i + 1 >= argc) {
					missingArgument();
					return 0;
				}
				else {
					transformMode = argv[++i][0];
				}
			}
			else {
				cout << "Error starting program!" << endl;
				instruction();
				return 0;
			}
		}

		// Execute the appropriate mode based on the parsed arguments
		if (mode == "auto") {
			benchmark.runBenchmark();
			return 0;
		}
		else if (mode == "custom") {
			if (inputFile.empty() || (transformMode != 'f' && transformMode != 'i') || repetitions <= 0) {
				cout << "Invalid arguments for custom mode!" << endl;
				instruction();
				return 0;
			}
			else {
				benchmark.runCustomBenchmark(inputFile, transformMode, repetitions);
				return 0;
			}
		}
		else if (mode == "dft" || mode == "fft") {
			if (inputFile.empty() || (transformMode != 'f' && transformMode != 'i')) {
				cout << "Invalid arguments for [dft|fft] mode!" << endl;
				instruction();
				return 0;
			}
			else {
				FileIO fileIO;
				if (mode == "dft") {
					DFT dft;
					if (transformMode == 'f') {
						fileIO.writeSpectrum(dft.compute(fileIO.readSignal(inputFile)), outputFile);
						return 0;
					}
					else if (transformMode == 'i') {
						fileIO.writeSignal(dft.computeInverse(fileIO.readSpectrum(inputFile)), outputFile);
						return 0;
					}
					else {
						cout << "Error selecting [f|i]!" << endl;
						instruction();
						return 0;
					}
				}
				else if (mode == "fft") {
					FFT fft;
					if (transformMode == 'f') {
						fileIO.writeSpectrum(fft.compute(fileIO.readSignal(inputFile)), outputFile);
						return 0;
					}
					else if (transformMode == 'i') {
						fileIO.writeSignal(fft.computeInverse(fileIO.readSpectrum(inputFile)), outputFile);
						return 0;
					}
					else {
						cout << "Error selecting [f|i]!" << endl;
						instruction();
						return 0;
					}
				}
			}
		}
		else {
			cout << "Error selecting mode!" << endl;
			instruction();
			return 0;
		}
	}
	catch (const exception& error) {
		cout << error.what() << endl;
	}
}