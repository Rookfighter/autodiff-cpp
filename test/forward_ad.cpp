/*
 * forward_ad.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#include <catch.hpp>
#include "adcpp/forward_ad.h"

using namespace fad;

TEST_CASE("forward algorithmic differentiation")
{
    double eps = 1e-6;
    SECTION("add constant")
    {
        Double x(3,1);
        double c = 2;

        Double f = c + x;

        REQUIRE(Approx(5).margin(eps) == f.value);
        REQUIRE(Approx(1).margin(eps) == f.gradient);
    }

    SECTION("multiply constant")
    {
        Double x(3,1);
        double c = 2;

        Double f = c * x;

        REQUIRE(Approx(6).margin(eps) == f.value);
        REQUIRE(Approx(2).margin(eps) == f.gradient);
    }

    SECTION("divide constant")
    {
        Double x(2,1);
        double c = 4;

        Double f = c / x;

        REQUIRE(Approx(2).margin(eps) == f.value);
        REQUIRE(Approx(-0.5).margin(eps) == f.gradient);
    }

    SECTION("divide by constant")
    {
        Double x(3,1);
        double c = 2;

        Double f = x / c;

        REQUIRE(Approx(1.5).margin(eps) == f.value);
        REQUIRE(Approx(0.5).margin(eps) == f.gradient);
    }

    SECTION("sine")
    {
        Double x(3,1);
        double valExp = std::sin(x.value);
        double gradExp = std::cos(x.value);

        Double f = sin(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value);
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient);
    }

    SECTION("cosine")
    {
        Double x(3,1);
        double valExp = std::cos(x.value);
        double gradExp = -std::sin(x.value);

        Double f = cos(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value);
        REQUIRE(Approx(gradExp).margin(eps) == f.gradient);
    }
}
