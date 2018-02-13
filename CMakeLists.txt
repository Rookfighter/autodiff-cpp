cmake_minimum_required(VERSION 3.5)
project(ad-cpp)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall")

include_directories(
	"include"
)

add_executable(fad "src/fad.cpp")
