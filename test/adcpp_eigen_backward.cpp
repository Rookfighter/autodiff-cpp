/* adcpp_eigen_backward.cpp
 *
 *  Created on: 21 Aug 2019
 *      Author: Fabian Meyer
 */

#include <catch2/catch.hpp>
#include <adcpp_eigen.h>

using namespace adcpp;

TEST_CASE("Eigen backward algorithmic differentiation")
{
    double eps = 1e-6;

    SECTION("exp")
    {
        bwd::Vector2d x;
        x << bwd::Double(3), bwd::Double(2);

        Eigen::Vector2d valExp;
        valExp <<
            std::exp(x(0).value()),std::exp(x(1).value());
        Eigen::Matrix2d jacExp;
        jacExp << std::exp(x(0).value()), 0,
            0, std::exp(x(1).value());

        bwd::Vector2d f = x.array().exp();

        REQUIRE(Approx(valExp(0)).margin(eps) == f(0).value());
        REQUIRE(Approx(valExp(1)).margin(eps) == f(1).value());

        f(0).setGradient(1);
        REQUIRE(Approx(jacExp(0, 0)).margin(eps) == x(0).gradient());
        REQUIRE(Approx(jacExp(0, 1)).margin(eps) == x(1).gradient());

        f(0).unsetGradient();
        f(1).setGradient(1);
        REQUIRE(Approx(jacExp(1, 0)).margin(eps) == x(0).gradient());
        REQUIRE(Approx(jacExp(1, 1)).margin(eps) == x(1).gradient());
    }

    SECTION("multiple outputs")
    {
        bwd::Vector2d x;
        x << bwd::Double(3), bwd::Double(2);

        bwd::Matrix2d c;
        c << bwd::Double(2.1), bwd::Double(3.4),
            bwd::Double(1.6), bwd::Double(2.3);

        Eigen::Vector2d valExp;
        valExp <<
            x(0).value() * c(0, 0).value() +  x(1).value() * c(0, 1).value(),
            x(0).value() * c(1, 0).value() +  x(1).value() * c(1, 1).value();
        Eigen::Matrix2d jacExp;
        jacExp << c(0, 0).value(), c(0, 1).value(),
            c(1, 0).value(), c(1, 1).value();

        bwd::Vector2d f = c * x;

        REQUIRE(Approx(valExp(0)).margin(eps) == f(0).value());
        REQUIRE(Approx(valExp(1)).margin(eps) == f(1).value());

        f(0).setGradient(1);
        REQUIRE(Approx(jacExp(0, 0)).margin(eps) == x(0).gradient());
        REQUIRE(Approx(jacExp(0, 1)).margin(eps) == x(1).gradient());

        f(0).unsetGradient();
        f(1).setGradient(1);
        REQUIRE(Approx(jacExp(1, 0)).margin(eps) == x(0).gradient());
        REQUIRE(Approx(jacExp(1, 1)).margin(eps) == x(1).gradient());
    }
}
