#include "distances.hpp"
#include "similarity.hpp"

#include <cmath>
#include <iostream>
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

    return sqrt(res);
}

template<typename T>
auto standard_euclidean_distance(const T x1, const T x2) -> f64 {
    if (x1.size() != x2.size()) {
        cerr << "Invalid input size. " << x1.size() << " : " << x2.size() << endl;
        exit(1);
    }

    f64 res = 0;
    for (int i=0; i<x1.size(); ++i) {
        f64 ave = (x1[i] + x2[i]) / 2;
        f64 s = (pow(x1[i]-ave, 2) + pow(x2[i]-ave, 2)) / 2;
        if(s==0) continue;
        res += pow(abs(x1[i] - x2[i]), 2) / s;
    }

    return sqrt(res);
}

template<typename T>
auto cosine_distance(const T x1, const T x2) -> f64 {
    return cpplearn::similarity::cosine_similarity(x1, x2);
}

template f64 euclidean_distance(const vector<i32>, const vector<i32>);
template f64 euclidean_distance(const vector<i64>, const vector<i64>);
template f64 euclidean_distance(const vector<f64>, const vector<f64>);

template f64 standard_euclidean_distance(const vector<i32>, const vector<i32>);
template f64 standard_euclidean_distance(const vector<i64>, const vector<i64>);
template f64 standard_euclidean_distance(const vector<f64>, const vector<f64>);

template f64 cosine_distance(const vector<i32>, const vector<i32>);
template f64 cosine_distance(const vector<i64>, const vector<i64>);
template f64 cosine_distance(const vector<f64>, const vector<f64>);

} // namespace distances
} // namespace cpplearn
