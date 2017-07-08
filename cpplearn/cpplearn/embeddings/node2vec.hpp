#ifndef NODE2VEC_HPP
#define NODE2VEC_HPP

#include "embeddings/abstract_embeddings.hpp"

namespace cpplearn {
namespace embeddings {

template<typename T>
class node2vec : public abstract_embeddings<T> {
    public:
        node2vec();
        ~node2vec();

        auto fit(T) -> void;
};

} // namespace embeddings
} // namespace cpplearn

#endif
