#ifndef DISTANCES_HPP
#define DISTANCES_HPP

#include <vector>

namespace cpplearn {
namespace distances {

using i32 = int;
using i64 = long long;
using f64 = double;

template<typename T>
auto euclidean_distance(T, T) -> f64;

} // namespace distances
} // namespace cpplearn

#endif
