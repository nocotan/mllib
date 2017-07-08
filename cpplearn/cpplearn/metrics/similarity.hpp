#ifndef SIMILARITY_HPP
#define SIMILARITY_HPP

#include "data_type.hpp"

namespace cpplearn {
namespace similarity {

template<typename T>
auto cosine_similarity(T, T) -> f64;

template<typename T>
auto jaccard_similarity(T, T) -> f64;

template<typename T>
auto dice_similarity(T, T) -> f64;

template<typename T>
auto simpson_similarity(T, T) -> f64;

} // namespace similarity
} // namespace cpplearn

#endif
