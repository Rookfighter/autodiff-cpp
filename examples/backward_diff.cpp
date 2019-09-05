/* backward_diff.cpp
 *
 * Created On: 21 Aug 2019
 *     Author: Fabian Meyer
 */

#include <adcpp.h>
#include <iostream>
#include <string>

using namespace adcpp;

// define your function with adcpp numbers
static bwd::Double myfuncA(const bwd::Double &x,
    const bwd::Double &y)
{
    // constants have to be wrapped in adcpp numbers
    return bwd::Double(2) * bwd::pow(y * bwd::sin(x) + bwd::exp(x / y), 2);
}

// define a second function with adcpp numbers
static bwd::Double myfuncB(const bwd::Double &x,
    const bwd::Double &y)
{
    return bwd::sqrt(x * x / bwd::exp(y)) ;
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

    // Define x and y as adcpp Double in backward mode.
    bwd::Double x = bwd::Double(xval);
    bwd::Double y = bwd::Double(yval);
    // Evaluate the functions.
    bwd::Double fA = myfuncA(x, y);
    bwd::Double fB = myfuncB(x, y);

    // Compute the derivative of all input parameters with respect to the
    // given function
    bwd::Double::DerivativeMap derivative;
    fA.derivative(derivative);

    // Print the results.
    // value() is an accessors for the computed value of a function.
    // The derivative variable contains the derivative of different parameters
    // w.r.t. the function.
    // Call value on final function value to retrieve its result.
    // Use derivative on the variable of which you want partial derivatives for
    // the function.
    std::cout << "Result (A):" << std::endl
        << "x = " << xval << ", y = " << yval << std::endl
        << "f = " << fA.value()
        << ", fx = " << derivative(x)
        << ", fy = " << derivative(y) << std::endl;

    // Calculate the derivatives for a different function.
    // The derivative variable can be reused.
    fB.derivative(derivative);

    std::cout << "Result (B):" << std::endl
        << "x = " << xval << ", y = " << yval << std::endl
        << "f = " << fB.value()
        << ", fx = " << derivative(x)
        << ", fy = " << derivative(y) << std::endl;
    return 0;
}
