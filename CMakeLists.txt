cmake_minimum_required(VERSION 3.16)

project(fourierpk VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFTW3 REQUIRED fftw3)

add_executable(fourierpk
    src/main.cpp
    src/dft.cpp
    src/fft.cpp
)

target_include_directories(fourierpk PRIVATE
    ${FFTW3_INCLUDE_DIRS}
)

target_link_directories(fourierpk PRIVATE
    ${FFTW3_LIBRARY_DIRS}
)

target_link_libraries(fourierpk PRIVATE
    ${FFTW3_LIBRARIES}
)