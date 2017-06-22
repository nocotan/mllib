cmake_minimum_required(VERSION 2.8)
include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/metrics)
add_library(cluster STATIC
    abstract_cluster.cpp
    k_means.cpp
)
