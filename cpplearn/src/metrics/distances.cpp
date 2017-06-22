#include "distances.hpp"

#include <iostream>
#include <cmath>
#include <vector>

namespace cpplearn {
namespace distances {

using namespace std;

template<typename T>
auto euclidean_distance(T x1, T x2) -> f64 {
    if (x1.size() != x2.size()) {
        cerr << "Invalid input size. " << endl;
        exit(1);
    }

    f64 res = 0;
    for (int i=0; i<x1.size(); ++i) {
        res += pow(abs(x1[i] - x2[i]), 2);
    }

    return res;
}

template f64 euclidean_distance(vector<i32>, vector<i32>);
template f64 euclidean_distance(vector<i64>, vector<i64>);
template f64 euclidean_distance(vector<f64>, vector<f64>);

} // namespace distances
} // namespace cpplearn
