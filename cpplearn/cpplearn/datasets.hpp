#ifndef DATASETS_HPP
#define DATASETS_HPP

#include <string>
#include <tuple>
#include <vector>

namespace cpplearn {

using f64 = double;
using vec = std::vector<f64>;
using mat = std::vector<std::vector<f64> >;

struct target_url {
    static constexpr char iris[] = "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data";
};

class datasets {
    public:
        static auto load_iris() -> std::tuple<mat, vec>;
};
} // namespace cpplearn

#endif
