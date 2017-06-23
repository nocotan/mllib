#ifndef SIMILARITY_HPP
#define SIMILARITY_HPP

namespace cpplearn {
namespace similarity {

using i32 = int;
using i64 = long long;
using f64 = double;

template<typename T>
auto cosine_similarity(T, T) -> f64;

template<typename T>
auto jaccard_similarity(T, T) -> f64;

template<typename T>
auto dice_similarity(T, T) -> f64;

} // namespace similarity
} // namespace cpplearn

#endif
