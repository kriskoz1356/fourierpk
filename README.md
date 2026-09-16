# Fourier Transform Benchmark

A C++17 application for computing and benchmarking Fourier transforms. The program provides implementations of:

* Discrete Fourier Transform (DFT),
* Fast Fourier Transform (FFT),
* FFTW.

The program supports Fourier transform and inverse Fourier transform operations, as well as performance benchmarking.

## Requirements

* C++17 compatible compiler
* CMake 
* FFTW3
* Git (optional, for cloning the repository)

The project can be built on **Linux and Windows** using CMake.

## FFTW3 Installation

FFTW3 is required by the FFTW implementation.

### Ubuntu / Debian

```bash
sudo apt update
sudo apt install libfftw3-dev
```

To check the installed version:

```bash
pkg-config --modversion fftw3
```

If `pkg-config` is not installed:

```bash
sudo apt install pkg-config
```

## Build

The project uses CMake, so the build process is similar on Linux and Windows.

From the project root directory:

```bash
cmake -S . -B build
cmake --build build
```

## Running the Program

The executable is generated inside the `build` directory. Its exact location depends on the operating system and CMake generator.

>Remember: You have to be in the project folder!

### Linux

For a typical single-configuration build:

```bash
./build/fourierpk
```

## Program Usage

The program is controlled using command-line arguments.

### Available flags

| Flag   | Description                              |
| ------ | ---------------------------------------- |
| `-m`   | Mode of operation                        |
| `-in`  | Input file                               |
| `-out` | Output file                              |
| `-c`   | Number of benchmark repetitions          |
| `-fi`  | Forward (`f`) or inverse (`i`) transform |

The program provides three modes:

* `auto` - runs automatic benchmark tests,
* `custom` - runs a benchmark using a specified input file, transform direction and number of repetitions,
* `dft` - performs a DFT transform or inverse transform,
* `fft` - performs an FFT transform or inverse transform.

### Automatic benchmark

```bash
./build/fourierpk -m auto
```

Runs the automatic benchmark.

### Custom benchmark

```bash
./build/fourierpk -m custom -in data/signal.txt -fi f -c 9
```

Runs the benchmark 9 times using the signal from `data/signal.txt`.

For an inverse transform:

```bash
./build/fourierpk -m custom -in data/spectrum.txt -fi i -c 9
```

### DFT

Forward transform:

```bash
./build/fourierpk -m dft -in data/signal.txt -fi f -out data/output/dft_output.txt
```

Inverse transform:

```bash
./build/fourierpk -m dft -in data/spectrum.txt -fi i -out data/output/reconstructed_signal.txt
```

### FFT

Forward transform:

```bash
./build/fourierpk -m fft -in data/signal.txt -fi f -out data/output/fft_output.txt
```

Inverse transform:

```bash
./build/fourierpk -m fft -in data/spectrum.txt -fi i -out data/output/reconstructed_signal.txt
```

The `output` directory is created automatically when necessary.

## Input and Output Files

Real-valued signals are stored as one value per line:

```text
1.0
2.0
3.0
4.0
```

Spectra are stored as pairs of real and imaginary parts:

```text
10.0 0.0
-2.0 2.5
0.0 -1.0
```

Example project structure:

```text
project/
├── include/
├── src/
├── data/
│   ├── signal.txt
│   └── output/
├── tests/
├── CMakeLists.txt
└── README.md
```

Generated files in `data/output/` are not tracked by Git.

## Running from CMake / IDE

If the project is opened in an IDE with CMake support, the project can be configured, built and run using the IDE's CMake tools.

For example, in Visual Studio Code:

```text
CMake: Configure
CMake: Build
CMake: Run Without Debugging
```

The exact names of these commands may depend on the IDE and installed CMake extensions.
