#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <vector>

namespace cpplearn {
namespace cluster {

using i32 = int;
using i64 = long long;
using f64 = double;

using mati32 = std::vector<std::vector<i32> >;
using mati64 = std::vector<std::vector<i64> >;
using matf64 = std::vector<std::vector<f64> >;
using vecf64 = std::vector<f64>;

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
