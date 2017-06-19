#include "k_means.hpp"
#include "abstract_cluster.hpp"

namespace cpplearn {
namespace cluster {

template<typename T>
k_means<T>::k_means() {}

template<typename T>
k_means<T>::~k_means() {}

template<typename T>
auto k_means<T>::fit(T x) -> void {
}

template<typename T>
auto k_means<T>::fit_predict(T x) -> vecf64 {
}

template<typename T>
auto k_means<T>::predict(T x) -> vecf64 {
}


template k_means<matf64>::k_means();
template k_means<matf64>::~k_means();
template void k_means<mati32>::fit(mati32);
template void k_means<mati64>::fit(mati64);
template void k_means<matf64>::fit(matf64);
template vecf64 k_means<mati32>::fit_predict(mati32);
template vecf64 k_means<mati64>::fit_predict(mati64);
template vecf64 k_means<matf64>::fit_predict(matf64);
template vecf64 k_means<mati32>::predict(mati32);
template vecf64 k_means<mati64>::predict(mati64);
template vecf64 k_means<matf64>::predict(matf64);

} // namespace cluster
} // namespace cpplearn
