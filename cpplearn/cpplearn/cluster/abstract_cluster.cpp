#include "abstract_cluster.hpp"

namespace cpplearn {
namespace cluster {

template<typename T>
abstract_cluster<T>::abstract_cluster() { }

template<typename T>
abstract_cluster<T>::~abstract_cluster() { }

template abstract_cluster<mati32>::abstract_cluster();
template abstract_cluster<mati64>::abstract_cluster();
template abstract_cluster<matf64>::abstract_cluster();
template abstract_cluster<mati32>::~abstract_cluster();
template abstract_cluster<mati64>::~abstract_cluster();
template abstract_cluster<matf64>::~abstract_cluster();

} // namespace cluster
} // namespace abstract_cluster
