# CMakeLists.txt
#
#     Author: Fabian Meyer
# Created On: 30 Mar 2022
#    License: MIT

add_library(adcpp INTERFACE)
target_include_directories(adcpp INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
add_library(adcpp::adcpp ALIAS adcpp)

add_library(adcpp_eigen INTERFACE)
target_include_directories(adcpp_eigen INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(adcpp_eigen INTERFACE adcpp::adcpp Eigen3::Eigen)
add_library(adcpp::adcpp_eigen ALIAS adcpp_eigen)

install(DIRECTORY adcpp TYPE INCLUDE)