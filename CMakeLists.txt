# CMakeLists.txt
#
#     Author: Fabian Meyer
# Created On: 15 Aug 2018

cmake_minimum_required(VERSION 3.5)
project(adcpp)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(dep)

include_directories(
    "include"
    ${EIGEN3_INCLUDE_DIR}
)

install(FILES "include/adcpp.h" "include/adcpp_eigen.h"
    DESTINATION "include")

if(${BUILD_EXAMPLES})
    # Compile examples
    add_subdirectory(examples)
endif(${BUILD_EXAMPLES})

if(${BUILD_TESTS})
    # Compile examples
    add_subdirectory(test)
endif(${BUILD_TESTS})
