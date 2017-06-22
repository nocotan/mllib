#ifndef K_MEANS_HPP
#define K_MEANS_HPP

#include "abstract_cluster.hpp"
#include <string>
#include <tuple>

namespace cpplearn {
namespace cluster {

enum kmeans_algorithm {
    full,
    elkan,
};

template<typename T>
class k_means : public abstract_cluster<T> {
    private:
        i32 n_clusters;
        i32 max_iter;
        i32 n_init;
        kmeans_algorithm algorithm;

        T cluster_centers;
        vecf64 pred_result;
    public:
        k_means();
        k_means(i32);
        ~k_means();

        auto fit(T) -> void;
        auto predict(T) -> vecf64;
        auto fit_predict(T) -> vecf64;

        auto get_params() -> std::tuple<i32, i32, i32, std::string>;
        auto get_cluster_centers() -> T;

        auto set_n_clusters(i32) -> void;
        auto set_max_iter(i32) -> void;
        auto set_n_init(i32) -> void;
        auto set_algorithm(std::string) -> void;
};

} // namespace cluster
} // namespace cpplearn

#endif
