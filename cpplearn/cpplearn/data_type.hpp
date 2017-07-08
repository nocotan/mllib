#ifndef DATA_TYPE_HPP
#define DATA_TYPE_HPP

#include <vector>

namespace cpplearn {

using i32 = int;
using i64 = long long;
using f64 = double;

using veci32 = std::vector<i32>;
using veci64 = std::vector<i64>;
using vecf64 = std::vector<f64>;
using mati32 = std::vector<std::vector<i32> >;
using mati64 = std::vector<std::vector<i64> >;
using matf64 = std::vector<std::vector<f64> >;

};

#endif
