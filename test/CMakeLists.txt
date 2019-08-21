# CMakeLists.txt
#
#     Author: Fabian Meyer
# Created On: 21 Aug 2019

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${CATCH2_INCLUDE_DIR}
)

set(TEST_SRC
    "main.cpp"

    "adcpp_backward.cpp"
    "adcpp_forward.cpp"

    "adcpp_eigen_backward.cpp"
    "adcpp_eigen_forward.cpp"
)

add_executable(run_tests ${TEST_SRC})
