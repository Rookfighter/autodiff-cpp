/* adcpp_forward.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#include <iostream>
#include <catch2/catch.hpp>
#include <adcpp.h>

using namespace adcpp::fwd;

TEST_CASE("algorithmic differentiation forward mode")
{
    double eps = 1e-6;
    SECTION("add constant")
    {
        Double x(3, 1);
        double c = 2;

        double valExp = 5;
        double gradExp = 1;

        Double f = Double(c) + x;

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("multiply constant")
    {
        Double x(3, 1);
        double c = 2;

        double valExp = c * x.value();
        double gradExp = c;

        Double f = Double(c) * x;

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("divide constant")
    {
        Double x(3, 1);
        double c = 2;

        double valExp = c / x.value();
        double gradExp = -c / (x.value() * x.value());

        Double f = Double(c) / x;

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("divide by constant")
    {
        Double x(3, 1);
        double c = 2;

        double valExp = x.value() / c;
        double gradExp = 1 / c;

        Double f = x / Double(c);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("sine")
    {
        Double x(3, 1);
        double valExp = std::sin(x.value());
        double gradExp = std::cos(x.value());

        Double f = x.sin();

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("cosine")
    {
        Double x(3, 1);
        double valExp = std::cos(x.value());
        double gradExp = -std::sin(x.value());

        Double f = x.cos();

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("square root")
    {
        Double x(3, 1);
        double valExp = std::sqrt(x.value());
        double gradExp = 0.5 / std::sqrt(x.value());

        Double f = x.sqrt();

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("exponential")
    {
        Double x(3, 1);
        double valExp = std::exp(x.value());
        double gradExp = std::exp(x.value());

        Double f = x.exp();

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("power")
    {
        Double x(3, 1);
        double valExp = std::pow(x.value(), 2.3);
        double gradExp = 2.3 * std::pow(x.value(), 1.3);

        Double f = x.pow(2.3);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("abs")
    {
        Double x(-2, 1);
        double valExp = std::abs(x.value());
        double gradExp = 1;

        Double f = x.abs();

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }

    SECTION("abs2")
    {
        Double x(-2, 1);
        double valExp = x.value() * x.value();
        double gradExp = 2 * x.value();

        Double f = x.abs2();

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient());
    }
}
