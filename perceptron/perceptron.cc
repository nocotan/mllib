#include <iostream>
#include <vector>

using namespace std;

auto AND(int x1, int x2) -> int {
    vector<int> x{x1, x2};
    vector<double> w{0.5, 0.5};
    double b = -0.7;
    double tmp = b;
    for(int i=0; i<2; ++i) tmp += x[i] * w[i];

    return tmp <= 0 ? 0 : 1;
}

auto NAND(int x1, int x2) -> int {
    vector<int> x{x1, x2};
    vector<double> w{-0.5, -0.5};
    double b = 0.7;
    double tmp = b;
    for(int i=0; i<2; ++i) tmp += x[i] * w[i];

    return tmp <= 0 ? 0 : 1;
}

auto OR(int x1, int x2) -> int {
    vector<int> x{x1, x2};
    vector<double> w{0.5, 0.5};
    double b = -0.2;
    double tmp = b;
    for(int i=0; i<2; ++i) tmp += x[i] * w[i];

    return tmp <= 0 ? 0 : 1;
}

auto XOR(int x1, int x2) -> int {
    int s1 = NAND(x1, x2);
    int s2 = OR(x1, x2);
    int y = AND(s1, s2);

    return y;
}

auto main() -> int {
    cout << XOR(0, 0) << endl;
    cout << XOR(1, 0) << endl;
    cout << XOR(0, 1) << endl;
    cout << XOR(1, 1) << endl;
    return 0;
}
