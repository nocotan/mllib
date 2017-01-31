#include <iostream>
#include "activation.hh"
using namespace std;
using namespace mllib;

auto main() -> int {
    vector<long double> x{-1, 1, 2};

    vector<long double> x2 = Activation::sigmoid(x);
    for(auto el : x2) cout << el << endl;

    vector<long double> x3 = Activation::relu(x);
    for(auto el : x3) cout << el << endl;
}
