/* adcpp_eigen_forward.cpp
 *
 *  Created on: 21 Aug 2019
 *      Author: Fabian Meyer
 */

#include <catch2/catch.hpp>
#include <adcpp_eigen.h>

using namespace adcpp;

TEST_CASE("Eigen forward algorithmic differentiation")
{
    double eps = 1e-6;

    SECTION("exp")
    {
        fwd::Vector2d x;
        x << fwd::Double(3,1), fwd::Double(2,0);

        Eigen::Vector2d valExp;
        valExp <<
            std::exp(x(0).value()),std::exp(x(1).value());
        Eigen::Matrix2d jacExp;
        jacExp << std::exp(x(0).value()), 0,
            0, std::exp(x(1).value());

        fwd::Vector2d fx = x.array().exp();

        x << fwd::Double(3,0), fwd::Double(2,1);
        fwd::Vector2d fy = x.array().exp();

        REQUIRE(Approx(valExp(0)).margin(eps) == fx(0).value());
        REQUIRE(Approx(valExp(1)).margin(eps) == fx(1).value());
        REQUIRE(Approx(valExp(0)).margin(eps) == fy(0).value());
        REQUIRE(Approx(valExp(1)).margin(eps) == fy(1).value());

        REQUIRE(Approx(jacExp(0, 0)).margin(eps) == fx(0).gradient());
        REQUIRE(Approx(jacExp(1, 0)).margin(eps) == fx(1).gradient());
        REQUIRE(Approx(jacExp(0, 1)).margin(eps) == fy(0).gradient());
        REQUIRE(Approx(jacExp(1, 1)).margin(eps) == fy(1).gradient());
    }

    SECTION("multiple outputs")
    {
        fwd::Vector2d x;
        x << fwd::Double(3,1), fwd::Double(2,0);

        fwd::Matrix2d c;
        c << fwd::Double(2.1), fwd::Double(3.4),
            fwd::Double(1.6), fwd::Double(2.3);

        Eigen::Vector2d valExp;
        valExp <<
            x(0).value() * c(0, 0).value() +  x(1).value() * c(0, 1).value(),
            x(0).value() * c(1, 0).value() +  x(1).value() * c(1, 1).value();
        Eigen::Matrix2d jacExp;
        jacExp << c(0, 0).value(), c(0, 1).value(),
            c(1, 0).value(), c(1, 1).value();

        fwd::Vector2d fx = c * x;

        x << fwd::Double(3,0), fwd::Double(2,1);
        fwd::Vector2d fy = c * x;

        REQUIRE(Approx(valExp(0)).margin(eps) == fx(0).value());
        REQUIRE(Approx(valExp(1)).margin(eps) == fx(1).value());
        REQUIRE(Approx(valExp(0)).margin(eps) == fy(0).value());
        REQUIRE(Approx(valExp(1)).margin(eps) == fy(1).value());

        REQUIRE(Approx(jacExp(0, 0)).margin(eps) == fx(0).gradient());
        REQUIRE(Approx(jacExp(1, 0)).margin(eps) == fx(1).gradient());
        REQUIRE(Approx(jacExp(0, 1)).margin(eps) == fy(0).gradient());
        REQUIRE(Approx(jacExp(1, 1)).margin(eps) == fy(1).gradient());
    }
}
