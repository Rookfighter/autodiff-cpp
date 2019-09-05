/* forward_diff.cpp
 *
 * Created On: 21 Aug 2019
 *     Author: Fabian Meyer
 */

#include <adcpp.h>
#include <iostream>
#include <string>

using namespace adcpp;

// define your function with adcpp numbers
static fwd::Double myfunc(const fwd::Double &x,
    const fwd::Double &y)
{
    // constants have to be wrapped in adcpp numbers
    return fwd::Double(2) * fwd::pow(y * fwd::sin(x) + fwd::exp(x / y), 2);
}

int main(const int argc, const char **argv)
{
    if(argc != 3)
    {
        std::cout << "Usage: forward_diff <xval> <yval>" << std::endl;
        return 1;
    }

    // parse command line arguments as regular doubles
    double xval = std::stod(argv[1]);
    double yval = std::stod(argv[2]);

    // Define x and y as adcpp Double
    // The first parameter defines its value and the second value defines its
    // derivative.
    // Set the derivative of x to 1, so we can calculate the partial derivative
    // of our function w.r.t. to x.
    fwd::Double x = fwd::Double(xval, 1);
    fwd::Double y = fwd::Double(yval, 0);
    // Evaluate the function with respect to x.
    fwd::Double fx = myfunc(x, y);

    // Set the derivative of y to 1, so we can calculate the partial derivative
    // of our function w.r.t. to y.
    x = fwd::Double(xval, 0);
    y = fwd::Double(yval, 1);
    // Evaluate the function with respect to y.
    fwd::Double fy = myfunc(x, y);

    // Print the results.
    // value() and derivative() are accessors for the derivative and computed value
    // of a function.
    std::cout << "Result:" << std::endl
        << "x = " << xval << ", y = " << yval << std::endl
        << "f = " << fx.value()
        << ", fx = " << fx.derivative()
        << ", fy = " << fy.derivative() << std::endl;
    return 0;
}
