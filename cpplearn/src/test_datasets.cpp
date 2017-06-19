//#define _GRIBCXX_DEBUG
#include <bits/stdc++.h>
#include "datasets.hpp"
using namespace std;

#define int long long

auto main() -> signed {
    vector<vector<double> > X;
    vector<double> y;
    tie(X, y) = cpplearn::datasets::load_iris();

    cout << "[";
    for(int i=0; i<X.size(); ++i) {
        cout << "[";
        for(int j=0; j<X[i].size(); ++j) cout << X[i][j] << " ";
        cout << "]," << endl;
    }
    cout << "]";
    cout << endl;

    cout << "[";
    for(int i=0; i<y.size(); ++i) cout << y[i] << " ";
    cout << "]";
    cout << endl;
    return 0;
}

