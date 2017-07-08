cmake_minimum_required(VERSION 2.8)
add_compile_options(-std=c++17)
include_directories(${PROJECT_SOURCE_DIR})
add_library(metrics STATIC
    distances.cpp
    similarity.cpp
)
target_link_libraries(metrics)
