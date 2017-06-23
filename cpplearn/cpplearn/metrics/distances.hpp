#ifndef DISTANCES_HPP
#define DISTANCES_HPP

namespace cpplearn {
namespace distances {

using i32 = int;
using i64 = long long;
using f64 = double;

template<typename T>
auto euclidean_distance(const T, const T) -> f64;

template<typename T>
auto standard_euclidean_distance(const T, const T) -> f64;

template<typename T>
auto cosine_distance(const T, const T) -> f64;

template<typename T>
auto manhattan_distance(const T, const T) -> f64;

template<typename T>
auto chebyshev_distance(const T, const T) -> f64;

} // namespace distances
} // namespace cpplearn

#endif
