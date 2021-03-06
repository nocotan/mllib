#ifndef ABSTRACT_EMBEDDINGS_HPP
#define ABSTRACT_EMBEDDINGS_HPP

#include "data_type.hpp"

namespace cpplearn {
namespace embeddings {

template<typename T>
class abstract_embeddings {
    protected:
        abstract_embeddings();
    public:
        virtual ~abstract_embeddings();
};

} // namespace embeddings
} // namespace cpplearn

#endif
