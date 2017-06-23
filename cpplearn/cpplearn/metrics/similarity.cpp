#include "similarity.hpp"

#include <cmath>
#include <iostream>
#include <set>
#include <vector>

namespace cpplearn {
namespace similarity {

using namespace std;

template<typename T>
auto cosine_similarity(const T x1, const T x2) -> f64 {
    if(x1.size() != x2.size()) {
        cerr << "Invalid input size. " << x1.size() << " : " << x2.size() << endl;
    }
    f64 num = 0;
    f64 dim1 = 0;
    f64 dim2 = 0;
    for(int i=0; i<x1.size(); ++i) {
        num += x1[i] * x2[i];
        dim1 += pow(x1[i], 2);
        dim2 += pow(x2[i], 2);
    }

    return num / (sqrt(dim1) * sqrt(dim2));
}

template<typename T>
auto jaccard_similarity(const T x1, const T x2) -> f64 {
    f64 prod_num = 0;
    for(auto itr=x1.begin(); itr!=x1.end(); ++itr) {
        prod_num += x2.count(*itr);
    }

    T union_st = x1;
    union_st.insert(x2.begin(), x2.end());

    return prod_num / union_st.size();
}

template<typename T>
auto dice_similarity(const T x1, const T x2) -> f64 {
    f64 prod_num = 0;
    for(auto itr=x1.begin(); itr!=x1.end(); ++itr) {
        prod_num += x2.count(*itr);
    }

    return 2*prod_num / (x1.size() + x2.size());
}

template f64 cosine_similarity(const vector<i32>, const vector<i32>);
template f64 cosine_similarity(const vector<i64>, const vector<i64>);
template f64 cosine_similarity(const vector<f64>, const vector<f64>);

template f64 jaccard_similarity(const set<i32>, const set<i32>);
template f64 jaccard_similarity(const set<i64>, const set<i64>);
template f64 jaccard_similarity(const set<f64>, const set<f64>);

template f64 dice_similarity(const set<i32>, const set<i32>);
template f64 dice_similarity(const set<i64>, const set<i64>);
template f64 dice_similarity(const set<f64>, const set<f64>);

} // namespace similarity
} // namespace cpplearn
