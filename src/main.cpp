#include "dft.h"
#include <iostream>
using namespace std;

int main() {
    DFT dft;
    vector<complex<double>> input = { {0, 0}, {1, 0}, {0, 0}, {-1, 0} };
    vector<complex<double>> output = dft.compute(input);

    cout << "DFT Output:" << endl;
    for (const auto& val : output) {
        cout << val << endl;
    }

    return 0;
}