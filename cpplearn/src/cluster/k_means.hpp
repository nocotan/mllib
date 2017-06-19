#ifndef K_MEANS_HPP
#define K_MEANS_HPP

#include "abstract_cluster.hpp"

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
    public:
        k_means();
        ~k_means();

        auto fit(T) -> void;
        auto fit_predict(T) -> vecf64;
        auto predict(T) -> vecf64;
};

} // namespace cluster
} // namespace cpplearn

#endif
