#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

namespace cpplearn {

class utils {
    public:
        static auto split(const std::string&, char) -> std::vector<std::string>;
};

} // namespace cpplearn

#endif
