# CMakeLists.txt
#
#     Author: Fabian Meyer
# Created On: 03 Apr 2022
#    License: MIT

configure_file(adcpp-config.in.cmake adcpp-config.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/adcpp-config.cmake" DESTINATION lib/adcpp)
