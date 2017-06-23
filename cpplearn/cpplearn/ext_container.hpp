#ifndef EXT_CONTAINER_HPP
#define EXT_CONTAINER_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

namespace cpplearn {

template<typename T>
auto operator+(const std::vector<T>& lhs, const std::vector<T>& rhs) -> std::vector<T> {
    if(lhs.size() != rhs.size()) {
        std::cerr << "Invalid input size: " <<
            lhs.size() << " : " << rhs.size() <<std::endl;
        exit(1);
    }
    std::vector<T> result(lhs.size());
    for(int i=0; i<lhs.size(); ++i) result[i] = lhs[i] + rhs[i];

    return result;
}

template<typename T, typename U>
auto operator/(const std::vector<T>& lhs, const U& rhs) -> std::vector<T> {
    std::vector<T> result(lhs.size());
    for(int i=0; i<lhs.size(); ++i) result[i] = lhs[i] / rhs;

    return result;
}

} // namespace cpplearn

#endif
