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

```autodiff-cpp``` can be used in forward mode as follows:

```cpp
#include <iostream>
#include <adcpp.h>

// define your function with adcpp numbers
static adcpp::fwd::Double myfunc(const adcpp::fwd::Double &x,
    const adcpp::fwd::Double &y)
{
    // constants have to be wrapped in adcpp numbers
    return adcpp::fwd::Double(2) * (y * x.sin() + (x / y).exp()).pow(2);
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
    adcpp::fwd::Double x = adcpp::fwd::Double(xval, 1);
    adcpp::fwd::Double y = adcpp::fwd::Double(yval, 0);
    // Evaluate the function with respect to x.
    adcpp::fwd::Double fx = myfunc(x, y);

    // Set the gradient of y to 1, so we can calculate the partial derivative
    // of our function w.r.t. to y.
    x = adcpp::fwd::Double(xval, 0);
    y = adcpp::fwd::Double(yval, 1);
    // Evaluate the function with respect to y.
    adcpp::fwd::Double fy = myfunc(x, y);

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
