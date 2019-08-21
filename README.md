# autodiff-cpp

![Cpp11](https://img.shields.io/badge/C%2B%2B-11-blue.svg)
![License](https://img.shields.io/packagist/l/doctrine/orm.svg)
![Travis Status](https://travis-ci.org/Rookfighter/autodiff-cpp.svg?branch=master)
![Appveyor Status](https://ci.appveyor.com/api/projects/status/uq730jam6he2o775?svg=true)

```autodiff-cpp``` is a single header-only C++ library for algorithmic (automatic)
differentiation.

## Install

Simply copy the header file into your project or install it using
the CMake build system by typing

```bash
cd path/to/repo
mkdir build
cd build
cmake ..
make install
```

You can use the CMake Find module in ```cmake/``` to find the installed header.

## Usage

Choose if you either want to use algorithmic differentiation in backward
or forward mode. The result and precision are the same in both cases but
the differentiation mode makes a difference performance-wise.

Forward mode is linear in the number of input arguments of your function.
If your function requires ```n``` input arguments, then the runtime behavior
is ```O(n)```. Basically the function has to be evaluated ```n``` times to
calculate the full gradient / Jacobian.

Backward mode is linear in the number of output values of your function.
If your function produces ```m``` output arguments, then the runtime behavior
is ```O(m)```. Basically the function has to be evaluated ```m``` times to
calculate the full gradient / Jacobian.

### Foward Mode

```cpp
#include <iostream>
#include <adcpp.h>

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
    // gradient.
    // Set the gradient of x to 1, so we can calculate the partial derivative
    // of our function w.r.t. to x.
    fwd::Double x = fwd::Double(xval, 1);
    fwd::Double y = fwd::Double(yval, 0);
    // Evaluate the function with respect to x.
    fwd::Double fx = myfunc(x, y);

    // Set the gradient of y to 1, so we can calculate the partial derivative
    // of our function w.r.t. to y.
    x = fwd::Double(xval, 0);
    y = fwd::Double(yval, 1);
    // Evaluate the function with respect to y.
    fwd::Double fy = myfunc(x, y);

    // Print the results.
    // value() and gradient() are accessors for the gradient and computed value
    // of a function.
    std::cout << "Result:" << std::endl
        << "x = " << xval << ", y = " << yval << std::endl
        << "f = " << fx.value()
        << ", fx = " << fx.gradient()
        << ", fy = " << fy.gradient() << std::endl;
    return 0;
}
```

### Backward Mode

```cpp
#include <iostream>
#include <adcpp.h>

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

    // Set the gradient of the function value, of which we want to compute the
    // gradient
    fA.setGradient(1);

    // Print the results.
    // value() and gradient() are accessors for the gradient and computed value
    // of a function.
    // Call value on final function value to retrieve its result.
    // Call gradient on the variable of which you want partial derivatives for
    // the function.
    std::cout << "Result (A):" << std::endl
        << "x = " << xval << ", y = " << yval << std::endl
        << "f = " << fA.value()
        << ", fx = " << x.gradient()
        << ", fy = " << y.gradient() << std::endl;

    // if you want calculate the derivative of a different function value, make
    // sure to unset the gradient of the previous value.
    fA.unsetGradient();
    // Set the gradient of function value B.
    fB.setGradient(1);
    std::cout << "Result (B):" << std::endl
        << "x = " << xval << ", y = " << yval << std::endl
        << "f = " << fB.value()
        << ", fx = " << x.gradient()
        << ", fy = " << y.gradient() << std::endl;
    return 0;
}
```
