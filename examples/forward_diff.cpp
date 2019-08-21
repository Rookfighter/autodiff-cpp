/* forward_diff.cpp
 *
 * Created On: 21 Aug 2019
 *     Author: Fabian Meyer
 */

#include <iostream>
#include <adcpp.h>

int main(const int argc, const char **argv)
{
    if(argc != 3)
    {
        std::cout << "Usage: forward_diff <xval> <yval>" << std::endl;
        return 1;
    }

    double x = std::stod(argv[1]);
    double y = std::stod(argv[2]);

    adcpp::fwd::Double xval = adcpp::fwd::Double(x, 1);
    adcpp::fwd::Double yval = adcpp::fwd::Double(y, 0);;
    adcpp::fwd::Double fval = (yval * xval.sin() + (xval / yval).exp()).pow(2);

    double fdx = fval.gradient();

    xval = adcpp::fwd::Double(x, 0);
    yval = adcpp::fwd::Double(y, 1);
    fval = (yval * xval.sin() + (xval / yval).exp()).pow(2);

    double fdy = fval.gradient();

    std::cout << "Result:" << std::endl
        << "x = " << x << ", y = " << y << std::endl
        << "f = " << fval.value() << ", fdx = " << fdx << ", fdy = " << fdy << std::endl;
    return 0;
}
