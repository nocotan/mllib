cmake_minimum_required(VERSION 2.8)
add_compile_options(-std=c++17)
add_subdirectory(cluster)
add_executable(test test.cpp)
add_library(core STATIC
    datasets.cpp
    http_downloader.cpp
    utils.cpp
)
target_link_libraries(test core cluster curl)
