#ifndef EXT_CONTAINER_HPP
#define EXT_CONTAINER_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template<typename T>
std::vector<T> operator+(const std::vector<T>& lhs, const std::vector<T>& rhs) {
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
std::vector<T> operator/(const std::vector<T>& lhs, const U& rhs) {
    std::vector<T> result(lhs.size());
    for(int i=0; i<lhs.size(); ++i) result[i] = lhs[i] / rhs;

    return result;
}

#endif
