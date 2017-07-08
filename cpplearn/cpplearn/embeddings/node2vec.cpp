#include "embeddings/node2vec.hpp"

namespace cpplearn {
namespace embeddings {

template<typename T>
node2vec<T>::node2vec() { }

template<typename T>
node2vec<T>::~node2vec() { }

template<typename T>
auto node2vec<T>::fit(T graph) -> void { }

template class node2vec<mati32>;
template class node2vec<mati64>;
template class node2vec<matf64>;

}
}
