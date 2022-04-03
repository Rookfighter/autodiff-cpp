# CMakeLists.txt
#
#     Author: Fabian Meyer
# Created On: 21 Aug 2019

add_executable(forward_diff "forward_diff.cpp")
target_link_libraries(forward_diff adcpp::adcpp)

add_executable(backward_diff "backward_diff.cpp")
target_link_libraries(backward_diff adcpp::adcpp)
