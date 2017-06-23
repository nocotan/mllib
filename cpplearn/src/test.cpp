//#define _GRIBCXX_DEBUG
#include "datasets.hpp"
#include "cluster/k_means.hpp"
#include "metrics/distances.hpp"

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
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

    cpplearn::cluster::k_means<vector<vector<double> > > kmeans;
    kmeans.set_n_clusters(3);
    kmeans.fit(X);
    auto&& pred = kmeans.predict();
    cout << "[";
    for(const auto& e : pred) cout << e << " ";
    cout << "]";
    cout << endl;

    cout << cpplearn::distances::cosine_distance(pred, y) << endl;
    return 0;
}

