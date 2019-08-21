# FindADCpp.txt
#
#     Author: Fabian Meyer
# Created On: 21 Aug 2019
#
# Defines
#   ADCPP_INCLUDE_DIR
#   ADCPP_FOUND

find_path(ADCPP_INCLUDE_DIR "adcpp.h"
    HINTS
    "${ADCPP_ROOT}/include"
    "$ENV{ADCPP_ROOT}/include"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ADCPP DEFAULT_MSG ADCPP_INCLUDE_DIR)
