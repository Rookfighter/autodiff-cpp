/* forward_diff.cpp
 *
 * Created On: 21 Aug 2019
 *     Author: Fabian Meyer
 */

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
