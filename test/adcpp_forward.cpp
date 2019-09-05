/* adcpp_forward.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#include <catch2/catch.hpp>
#include <adcpp.h>

using namespace adcpp;

TEST_CASE("forward algorithmic differentiation")
{
    double eps = 1e-6;
    SECTION("add constant")
    {
        fwd::Double x(3, 1);
        double c = 2;

        double valExp = 5;
        double gradExp = 1;

        fwd::Double f = fwd::Double(c) + x;

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("multiply constant")
    {
        fwd::Double x(3, 1);
        double c = 2;

        double valExp = c * x.value();
        double gradExp = c;

        fwd::Double f = fwd::Double(c) * x;

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("divide constant")
    {
        fwd::Double x(3, 1);
        double c = 2;

        double valExp = c / x.value();
        double gradExp = -c / (x.value() * x.value());

        fwd::Double f = fwd::Double(c) / x;

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("divide by constant")
    {
        fwd::Double x(3, 1);
        double c = 2;

        double valExp = x.value() / c;
        double gradExp = 1 / c;

        fwd::Double f = x / fwd::Double(c);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("sine")
    {
        fwd::Double x(3, 1);
        double valExp = std::sin(x.value());
        double gradExp = std::cos(x.value());

        fwd::Double f = fwd::sin(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("arcus sine")
    {
        fwd::Double x(0.5, 1);
        double valExp = std::asin(x.value());
        double gradExp = 1 / std::sqrt(1 - x.value() * x.value());

        fwd::Double f = fwd::asin(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("cosine")
    {
        fwd::Double x(3, 1);
        double valExp = std::cos(x.value());
        double gradExp = -std::sin(x.value());

        fwd::Double f = fwd::cos(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("arcus cosine")
    {
        fwd::Double x(0.5, 1);
        double valExp = std::acos(x.value());
        double gradExp = -1 / std::sqrt(1 - x.value() * x.value());

        fwd::Double f = fwd::acos(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("tangens")
    {
        fwd::Double x(3, 1);
        double valExp = std::tan(x.value());
        double c = std::cos(x.value());
        double gradExp = 1 / (c * c);

        fwd::Double f = fwd::tan(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("arcus tangens")
    {
        fwd::Double x(3, 1);
        double valExp = std::atan(x.value());
        double gradExp = 1 / (1 + x.value() * x.value());

        fwd::Double f = fwd::atan(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("arcus tangens 2")
    {
        fwd::Double x(3, 1);
        fwd::Double y(1, 0);
        double valExp = std::atan2(y.value(), x.value());
        double denom = y.value() * y.value() + x.value() * x.value();

        double gradXExp = y.value() / denom;

        fwd::Double fx = fwd::atan2(y, x);

        x = fwd::Double(3, 0);
        y = fwd::Double(1, 1);

        double gradyExp = x.value() / denom;

        fwd::Double fy = fwd::atan2(y, x);

        REQUIRE(Approx(valExp).margin(eps) == fx.value());
        REQUIRE(Approx(valExp).margin(eps) == fy.value());
        REQUIRE(Approx(gradXExp).margin(eps) == fx.derivative());
        REQUIRE(Approx(gradyExp).margin(eps) == fy.derivative());
    }

    SECTION("square root")
    {
        fwd::Double x(3, 1);
        double valExp = std::sqrt(x.value());
        double gradExp = 0.5 / std::sqrt(x.value());

        fwd::Double f = fwd::sqrt(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("exponential")
    {
        fwd::Double x(3, 1);
        double valExp = std::exp(x.value());
        double gradExp = std::exp(x.value());

        fwd::Double f = fwd::exp(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("power")
    {
        fwd::Double x(3, 1);
        double valExp = std::pow(x.value(), 2.3);
        double gradExp = 2.3 * std::pow(x.value(), 1.3);

        fwd::Double f = fwd::pow(x, 2.3);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("abs")
    {
        fwd::Double x(-2, 1);
        double valExp = std::abs(x.value());
        double gradExp = 1;

        fwd::Double f = fwd::abs(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("abs2")
    {
        fwd::Double x(-2, 1);
        double valExp = x.value() * x.value();
        double gradExp = 2 * x.value();

        fwd::Double f = fwd::abs2(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("log")
    {
        fwd::Double x(3, 1);
        double valExp = std::log(x.value());
        double gradExp = 1 / x.value();

        fwd::Double f = fwd::log(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("log2")
    {
        fwd::Double x(3, 1);
        double valExp = std::log2(x.value());
        double gradExp = 1 / (x.value() * std::log(2));

        fwd::Double f = fwd::log2(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("explicit cast")
    {
        fwd::Double x1(3, 1);
        double x2 = static_cast<double>(x1);

        REQUIRE(x1.value() == x2);

        x2 = 15;
        x1 = static_cast<fwd::Double>(x2);

        REQUIRE(x1.value() == x2);
        REQUIRE(x1.derivative() == 0);
    }

    SECTION("implicit cast")
    {
        double x2 = 15;
        fwd::Double x1 = x2;

        REQUIRE(x1.value() == x2);
        REQUIRE(x1.derivative() == 0);
    }

    SECTION("equality")
    {
        fwd::Double x1(1, 1);
        fwd::Double x2(1, 0);
        fwd::Double x3(2, 0);

        REQUIRE(x1 == x2);
        REQUIRE(x1 != x3);
    }

    SECTION("less than")
    {
        fwd::Double x1(-1, 1);
        fwd::Double x2(1, 0);
        fwd::Double x3(2, 0);

        REQUIRE(x1 < x2);
        REQUIRE(!(x3 < x2));
    }

    SECTION("less equal than")
    {
        fwd::Double x1(1, 1);
        fwd::Double x2(1, 0);
        fwd::Double x3(2, 0);

        REQUIRE(x1 <= x2);
        REQUIRE(x2 <= x3);
        REQUIRE(!(x3 <= x2));
    }

    SECTION("greater than")
    {
        fwd::Double x1(-1, 1);
        fwd::Double x2(1, 0);
        fwd::Double x3(2, 0);

        REQUIRE(x2 > x1);
        REQUIRE(!(x1 > x2));
    }

    SECTION("greater equal than")
    {
        fwd::Double x1(1, 1);
        fwd::Double x2(1, 0);
        fwd::Double x3(2, 0);

        REQUIRE(x2 >= x1);
        REQUIRE(x3 >= x2);
        REQUIRE(!(x2 >= x3));
    }

    SECTION("multiple variables")
    {
        fwd::Double x(3, 1);
        fwd::Double y(2, 0);

        double valExp = std::exp(x.value() + y.value() / x.value());

        double gradXExp = (1 - y.value() / (x.value() * x.value())) * valExp;
        fwd::Double fx = fwd::exp(x + y / x);

        x = fwd::Double(3, 0);
        y = fwd::Double(2, 1);
        double gradYExp = (1 / x.value()) * valExp;
        fwd::Double fy = fwd::exp(x + y / x);

        REQUIRE(Approx(valExp).margin(eps) == fx.value());
        REQUIRE(Approx(valExp).margin(eps) == fy.value());
        REQUIRE(Approx(gradXExp).margin(eps) == fx.derivative());
        REQUIRE(Approx(gradYExp).margin(eps) == fy.derivative());
    }
}
