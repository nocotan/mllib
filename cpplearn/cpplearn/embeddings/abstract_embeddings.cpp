#include "embeddings/abstract_embeddings.hpp"

namespace cpplearn {
namespace embeddings {

template<typename T>
abstract_embeddings<T>::abstract_embeddings() { }

template<typename T>
abstract_embeddings<T>::~abstract_embeddings() { }

template class abstract_embeddings<mati32>;
template class abstract_embeddings<mati64>;
template class abstract_embeddings<matf64>;

} // namespace embeddings
} // namespace cpplearn
