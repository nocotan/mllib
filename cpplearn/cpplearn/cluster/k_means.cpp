#include "cluster/abstract_cluster.hpp"
#include "cluster/k_means.hpp"
#include "metrics/distances.hpp"
#include "ext_container.hpp"

#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <tuple>

namespace cpplearn {
namespace cluster {
using namespace std;

template<typename T>
k_means<T>::k_means()
  :n_clusters(8), max_iter(300),
   n_init(10), algorithm(kmeans_algorithm::elkan) { }

template<typename T>
k_means<T>::k_means(i32 n_clusters)
  :n_clusters(n_clusters), max_iter(300),
   n_init(10), algorithm(kmeans_algorithm::elkan) { }

template<typename T>
k_means<T>::~k_means() {}

template<typename T>
auto k_means<T>::fit(T x) -> void {
    veci64 initial_centroid_indexes;

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, x.size()-1);

    for (int i=0; i<n_clusters; ++i) {
        i64 target_idx = 0;
        while(true) {
            target_idx = dist(mt);
            bool is_new = true;
            for(int j=0; j<cluster_centers.size(); ++j) {
                if(cluster_centers[j] == x[target_idx]) is_new = false;
            }
            if(is_new) break;
        }
        initial_centroid_indexes.push_back(target_idx);

        cluster_centers.push_back(x[target_idx]);
    }

   vecf64 pred(x.size(), 0);
   for(int i=0; i<max_iter; ++i) {
       vecf64 new_pred = pred;
       for(int j=0; j<x.size(); ++j) {
           f64 min_dist = 1e+9;
           i32 target_idx = 0;
           for(int k=0; k<cluster_centers.size(); ++k) {
               f64 cur_dist = distances::euclidean_distance(x[j], cluster_centers[k]);
               if(cur_dist < min_dist) {
                   min_dist = cur_dist;
                   target_idx = k;
               }
           }
           new_pred[j] = target_idx;
       }

       if(new_pred == pred) break;
       pred = new_pred;

        T features(n_clusters);
        veci64 memo(n_clusters);
        for(int j=0; j<x.size(); ++j) {
            if(features[pred[j]].size()==0) features[pred[j]] = x[j];
            else features[pred[j]] = features[pred[j]] + x[j];
            memo[pred[j]]++;
        }

        for(int j=0; j<features.size(); ++j) features[j] = features[j] / memo[j];
        this->cluster_centers = features;
   }
   this->pred_result = pred;
}

template<typename T>
auto k_means<T>::predict(T x) -> vecf64 {
    vecf64 pred;
    for(int i=0; i<x.size(); ++i) {
        f64 min_dist = 1e+9;
        i32 k = 0;
        for(int j=0; j<n_clusters; ++j) {
            f64 dist = distances::euclidean_distance(cluster_centers[j], x[i]);
            if(dist < min_dist) {
                min_dist = dist;
                k = j;
            }
        }
        pred.push_back(k);
    }

    return pred;
}

template<typename T>
auto k_means<T>::fit_predict(T x) -> vecf64 {
    this->fit(x);
    return this->pred_result;
}

template<typename T>
auto k_means<T>::get_params() -> tuple<i32, i32, i32, string> {
    string algorithm_str = this->algorithm==kmeans_algorithm::full ? "full" : "elkan";
    return make_tuple(this->n_clusters, this->max_iter, this->n_init, algorithm_str);
}

template<typename T>
auto k_means<T>::get_cluster_centers() -> T {
    return this->cluster_centers;
}

template<typename T>
auto k_means<T>::set_n_clusters(i32 n_clusters) -> void {
    this->n_clusters = n_clusters;
}

template<typename T>
auto k_means<T>::set_max_iter(i32 max_iter) -> void {
    this->max_iter = max_iter;
}

template<typename T>
auto k_means<T>::set_n_init(i32 n_init) -> void {
    this->n_init = n_init;
}

template<typename T>
auto k_means<T>::set_algorithm(string algorithm) -> void {
    if (algorithm == "full") this->algorithm = kmeans_algorithm::full;
    else if(algorithm == "elkan") this->algorithm = kmeans_algorithm::elkan;
    else {
        cerr << "Unknown algorithm: " << algorithm << endl;
        exit(1);
    }
}

template class k_means<mati32>;
template class k_means<mati64>;
template class k_means<matf64>;

} // namespace cluster
} // namespace cpplearn
