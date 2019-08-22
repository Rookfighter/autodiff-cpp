/* adcpp_forward.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#include <catch2/catch.hpp>
#include <adcpp.h>

using namespace adcpp;

TEST_CASE("backward algorithmic differentiation")
{
    double eps = 1e-6;
    SECTION("add constant")
    {
        bwd::Double x(3);
        double c = 2;

        double valExp = 5;
        double gradExp = 1;

        bwd::Double f = bwd::Double(c) + x;
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("multiply constant")
    {
        bwd::Double x(3);
        double c = 2;

        double valExp = c * x.value();
        double gradExp = c;

        bwd::Double f = bwd::Double(c) * x;
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("divide constant")
    {
        bwd::Double x(3);
        double c = 2;

        double valExp = c / x.value();
        double gradExp = -c / (x.value() * x.value());

        bwd::Double f = bwd::Double(c) / x;
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("divide by constant")
    {
        bwd::Double x(3);
        double c = 2;

        double valExp = x.value() / c;
        double gradExp = 1 / c;

        bwd::Double f = x / bwd::Double(c);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("sine")
    {
        bwd::Double x(3);
        double valExp = std::sin(x.value());
        double gradExp = std::cos(x.value());

        bwd::Double f = bwd::sin(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("arcus sine")
    {
        bwd::Double x(0.5);
        double valExp = std::asin(x.value());
        double gradExp = 1 / std::sqrt(1 - x.value() * x.value());

        bwd::Double f = bwd::asin(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("cosine")
    {
        bwd::Double x(3);
        double valExp = std::cos(x.value());
        double gradExp = -std::sin(x.value());

        bwd::Double f = bwd::cos(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("arcus cosine")
    {
        bwd::Double x(0.5);
        double valExp = std::acos(x.value());
        double gradExp = -1 / std::sqrt(1 - x.value() * x.value());

        bwd::Double f = bwd::acos(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("tangens")
    {
        bwd::Double x(3);
        double valExp = std::tan(x.value());
        double c = std::cos(x.value());
        double gradExp = 1 / (c * c);

        bwd::Double f = bwd::tan(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("arcus tangens")
    {
        bwd::Double x(3);
        double valExp = std::atan(x.value());
        double gradExp = 1 / (1 + x.value() * x.value());

        bwd::Double f = bwd::atan(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("arcus tangens 2")
    {
        bwd::Double x(3);
        bwd::Double y(1);
        double valExp = std::atan2(y.value(), x.value());
        double denom = y.value() * y.value() + x.value() * x.value();

        double gradXExp = y.value() / denom;
        double gradyExp = x.value() / denom;

        bwd::Double f = bwd::atan2(y, x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradXExp).margin(eps) == x.gradient());
        REQUIRE(Approx(gradyExp).margin(eps) == y.gradient());
    }

    SECTION("square root")
    {
        bwd::Double x(3);
        double valExp = std::sqrt(x.value());
        double gradExp = 0.5 / std::sqrt(x.value());

        bwd::Double f = bwd::sqrt(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("exponential")
    {
        bwd::Double x(3);
        double valExp = std::exp(x.value());
        double gradExp = std::exp(x.value());

        bwd::Double f = bwd::exp(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("power")
    {
        bwd::Double x(3);
        double valExp = std::pow(x.value(), 2.3);
        double gradExp = 2.3 * std::pow(x.value(), 1.3);

        bwd::Double f = bwd::pow(x, 2.3);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("abs")
    {
        bwd::Double x(-2);
        double valExp = std::abs(x.value());
        double gradExp = 1;

        bwd::Double f = bwd::abs(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("abs2")
    {
        bwd::Double x(-2);
        double valExp = x.value() * x.value();
        double gradExp = 2 * x.value();

        bwd::Double f = bwd::abs2(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("log")
    {
        bwd::Double x(3);
        double valExp = std::log(x.value());
        double gradExp = 1 / x.value();

        bwd::Double f = bwd::log(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("log2")
    {
        bwd::Double x(3);
        double valExp = std::log2(x.value());
        double gradExp = 1 / (x.value() * std::log(2));

        bwd::Double f = bwd::log2(x);
        f.setGradient(1);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == x.gradient());
    }

    SECTION("explicit cast")
    {
        bwd::Double x1(3);
        double x2 = static_cast<double>(x1);

        REQUIRE(x1.value() == x2);

        x2 = 15;
        x1 = static_cast<bwd::Double>(x2);

        REQUIRE(x1.value() == x2);
        REQUIRE(x1.gradient() == 0);
    }

    SECTION("implicit cast")
    {
        double x2 = 15;
        bwd::Double x1 = x2;

        REQUIRE(x1.value() == x2);
        REQUIRE(x1.gradient() == 0);
    }

    SECTION("equality")
    {
        bwd::Double x1(1);
        bwd::Double x2(1);
        bwd::Double x3(2);

        REQUIRE(x1 == x2);
        REQUIRE(x1 != x3);
    }

    SECTION("less than")
    {
        bwd::Double x1(-1);
        bwd::Double x2(1);
        bwd::Double x3(2);

        REQUIRE(x1 < x2);
        REQUIRE(!(x3 < x2));
    }

    SECTION("less equal than")
    {
        bwd::Double x1(1);
        bwd::Double x2(1);
        bwd::Double x3(2);

        REQUIRE(x1 <= x2);
        REQUIRE(x2 <= x3);
        REQUIRE(!(x3 <= x2));
    }

    SECTION("greater than")
    {
        bwd::Double x1(-1);
        bwd::Double x2(1);
        bwd::Double x3(2);

        REQUIRE(x2 > x1);
        REQUIRE(!(x1 > x2));
    }

    SECTION("greater equal than")
    {
        bwd::Double x1(1);
        bwd::Double x2(1);
        bwd::Double x3(2);

        REQUIRE(x2 >= x1);
        REQUIRE(x3 >= x2);
        REQUIRE(!(x2 >= x3));
    }

    SECTION("multiple variables")
    {
        bwd::Double x(3);
        bwd::Double y(2);

        double valExp = std::exp(x.value() + y.value() / x.value());
        double gradXExp = (1 - y.value() / (x.value() * x.value())) * valExp;
        double gradYExp = (1 / x.value()) * valExp;

        bwd::Double f = bwd::exp(x + y / x);
        f.setGradient(1);


        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradXExp).margin(eps) == x.gradient());
        REQUIRE(Approx(gradYExp).margin(eps) == y.gradient());
    }
}
