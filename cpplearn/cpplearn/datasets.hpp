#ifndef DATASETS_HPP
#define DATASETS_HPP

#include <string>
#include <tuple>
#include <vector>
#include "data_type.hpp"

namespace cpplearn {

struct target_url {
    static constexpr char iris[] = "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data";
    static constexpr char wine[] = "https://archive.ics.uci.edu/ml/machine-learning-databases/wine/wine.data";
};

class datasets {
    public:
        static auto load_iris() -> std::tuple<matf64, vecf64>;
        static auto load_wine() -> std::tuple<matf64, vecf64>;
};
} // namespace cpplearn

#endif
