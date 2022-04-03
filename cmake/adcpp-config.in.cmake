# adcpp-config.cmake
#
#     Author: Fabian Meyer
# Created On: 04 Apr 2022
#
# Defines
#   adcpp::adcpp
#   adcpp_INCLUDE_DIR
#   adcpp_FOUND

find_path(adcpp_INCLUDE_DIR
          adcpp/adcpp.hpp
          HINTS "@CMAKE_INSTALL_PREFIX@/include")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(adcpp DEFAULT_MSG adcpp_INCLUDE_DIR)

if(${adcpp_FOUND})
    add_library(adcpp INTERFACE)
    target_include_directories(adcpp INTERFACE "${adcpp_INCLUDE_DIR}")
    add_library(adcpp::adcpp ALIAS adcpp)

    if(${EIGEN3_FOUND})

    add_library(adcpp_eigen INTERFACE)
    target_include_directories(adcpp INTERFACE "${adcpp_INCLUDE_DIR}")
    target_link_libraries(adcpp_eigen INTERFACE adcpp::adcpp Eigen3::Eigen)
    add_library(adcpp::adcpp_eigen ALIAS adcpp_eigen)
    endif()
endif()