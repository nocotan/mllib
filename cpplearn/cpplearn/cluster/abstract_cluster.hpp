#ifndef ABSTRACT_CLUSTER_HPP
#define ABSTRACT_CLUSTER_HPP

#include <vector>
#include "data_type.hpp"

namespace cpplearn {
namespace cluster {

template<typename T>
class abstract_cluster {
    protected:
        abstract_cluster();
    public:
        virtual ~abstract_cluster();

        virtual auto fit(T) -> void = 0;
        virtual auto fit_predict(T) -> vecf64 = 0;
        virtual auto predict(T) -> vecf64 = 0;
};

} // namespace cluster
} // namespace cpplearn

#endif
