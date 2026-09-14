# Fourier - Programowanie Komputerów
Fourier Transform performance testing.

## Requirements

* C++17,
* CMake,
* GCC,
* FFTW

## FFTW3 How to install on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install libfftw3-dev
pkg-config --modversion fftw3 # Check the installed version

# If you do not have pkgconf install it:
sudo apt install pkgconf
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

or with CMake:

```bash
>CMake: Configure # Only for the first time

>CMake: Build
```

## Run

```bash
./build/fourierpk
```

or with CMake:

```bash
>CMake: Run Without Debugging
```
