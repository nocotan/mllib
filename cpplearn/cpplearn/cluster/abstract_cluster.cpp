#include "cluster/abstract_cluster.hpp"

namespace cpplearn {
namespace cluster {

template<typename T>
abstract_cluster<T>::abstract_cluster() { }

template<typename T>
abstract_cluster<T>::~abstract_cluster() { }

template class abstract_cluster<mati32>;
template class abstract_cluster<mati64>;
template class abstract_cluster<matf64>;

} // namespace cluster
} // namespace abstract_cluster
