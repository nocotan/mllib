#include "distances.hpp"

#include <iostream>
#include <cmath>
#include <vector>

namespace cpplearn {
namespace distances {

using namespace std;

template<typename T>
auto euclidean_distance(const T x1, const T x2) -> f64 {
    if (x1.size() != x2.size()) {
        cerr << "Invalid input size. " << x1.size() << " : " << x2.size() << endl;
        exit(1);
    }

    f64 res = 0;
    for (int i=0; i<x1.size(); ++i) {
        res += pow(abs(x1[i] - x2[i]), 2);
    }

    return res;
}

template f64 euclidean_distance(const vector<i32>, const vector<i32>);
template f64 euclidean_distance(const vector<i64>, const vector<i64>);
template f64 euclidean_distance(const vector<f64>, const vector<f64>);

} // namespace distances
} // namespace cpplearn
