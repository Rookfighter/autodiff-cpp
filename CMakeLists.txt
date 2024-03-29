# CMakeLists.txt
#
#     Author: Fabian Meyer
# Created On: 15 Aug 2018


cmake_minimum_required(VERSION 3.5)
project(adcpp)

option(BUILD_TESTS "Enables if tests should be built" OFF)
option(BUILD_EXAMPLES "Enables if examples should be built" OFF)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX /wd4127 /wd26495 /wd26451 /wd26812)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(dep)
add_subdirectory(include)
add_subdirectory(cmake)

if(${BUILD_TESTS})
    # Compile tests
    add_subdirectory(tests)
endif(${BUILD_TESTS})

if(${BUILD_EXAMPLES})
    # Compile examples
    add_subdirectory(examples)
endif(${BUILD_EXAMPLES})
