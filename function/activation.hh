#ifndef _ACTIVATION_FUNCTION_HPP
#define _ACTIVATION_FUNCTION_HPP

#include <algorithm>
#include <complex>
#include <vector>

namespace mllib {

using ld = long double;

class Activation {
    public:
        static const std::vector<ld> sigmoid(std::vector<ld> x) {
            std::vector<ld> res = x;
            for(int i=0; i<x.size(); ++i)
                res[i] = 1 / (1 + std::exp(-x[i]));

            return res;
        }

        static const std::vector<ld> relu(std::vector<ld> x) {
            std::vector<ld> res = x;
            for(int i=0; i<x.size(); ++i)
                res[i] = std::max((ld)0.0, x[i]);

            return res;
        }
};
} // namespace mllib

#endif
