cmake_minimum_required(VERSION 3.6)
project(mllib)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES stats/AbstractDistribution.h stats/Bernoulli.cpp stats/Bernoulli.h stats/Binom.cpp stats/Binom.h utils/ExtFunctions.h utils/ComplexStuff.h)
add_library(mllib SHARED ${SOURCE_FILES} stats/AbstractDistribution.h stats/Bernoulli.cpp stats/Bernoulli.h stats/Binom.cpp stats/Binom.h utils/ExtFunctions.h utils/ComplexStuff.h)
add_executable(UNITTEST stats/AbstractDistribution.h tests/unittest.cpp stats/Bernoulli.cpp stats/Bernoulli.h stats/Binom.cpp stats/Binom.h utils/ExtFunctions.h utils/ComplexStuff.h)