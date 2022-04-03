# CMakeLists.txt
#
#     Author: Fabian Meyer
# Created On: 21 Aug 2019
#    License: MIT

set(TEST_SRC
    "src/main.cpp"
    "src/adcpp_backward.test.cpp"
    "src/adcpp_forward.test.cpp"
    "src/adcpp_eigen_backward.test.cpp"
    "src/adcpp_eigen_forward.test.cpp"
)

add_executable(unittests ${TEST_SRC})
target_include_directories(unittests PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include")
target_link_libraries(unittests adcpp::adcpp_eigen Catch2::Catch2)