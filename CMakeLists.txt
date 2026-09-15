# CMake configuration for the Fourier Transform project
cmake_minimum_required(VERSION 3.16)

# Set the project name and version
project(fourierpk VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the FFTW3 library using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFTW3 REQUIRED fftw3)

# Add the source files for the Fourier Transform project
add_executable(fourierpk
    src/main.cpp
    src/dft/dft.cpp
    src/fft/fft.cpp
    src/fftw/fftw.cpp
    src/file-io/file-io.cpp
    src/benchmark/benchmark.cpp
)

# Include the Fourier Transform headers and FFTW3 headers
target_include_directories(fourierpk PRIVATE

    src
    src/dft
    src/fft
    src/fftw
    src/file-io
    data
    src/benchmark
    ${FFTW3_INCLUDE_DIRS}
)

# Link the FFTW3 library to the executable
target_link_directories(fourierpk PRIVATE
    ${FFTW3_LIBRARY_DIRS}
)

target_link_libraries(fourierpk PRIVATE
    ${FFTW3_LIBRARIES}
)