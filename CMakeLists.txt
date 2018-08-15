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
    ${CATCH2_INCLUDE_DIR}
    )


install(DIRECTORY include/adcpp DESTINATION include)
