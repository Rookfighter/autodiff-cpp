/* adcpp_forward.test.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#include <catch2/catch.hpp>
#include <adcpp/adcpp.hpp>

using namespace adcpp;

TEMPLATE_TEST_CASE("backward algorithmic differentiation", "[backward]", float, double)
{
    using Scalar = TestType;
    using ADScalar = bwd::Number<Scalar>;
    Scalar eps = 1e-6;
    SECTION("add constant")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar c = 2;

        Scalar valExp = 5;
        Scalar gradExp = 1;

        ADScalar f = ADScalar(c) + x;
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("multiply constant")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar c = 2;

        Scalar valExp = c * x.value();
        Scalar gradExp = c;

        ADScalar f = ADScalar(c) * x;
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("divide constant")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar c = 2;

        Scalar valExp = c / x.value();
        Scalar gradExp = -c / (x.value() * x.value());

        ADScalar f = ADScalar(c) / x;
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("divide by constant")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar c = 2;

        Scalar valExp = x.value() / c;
        Scalar gradExp = 1 / c;

        ADScalar f = x / ADScalar(c);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("sine")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar valExp = std::sin(x.value());
        Scalar gradExp = std::cos(x.value());

        ADScalar f = bwd::sin(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("arcus sine")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(0.5);
        Scalar valExp = std::asin(x.value());
        Scalar gradExp = 1 / std::sqrt(1 - x.value() * x.value());

        ADScalar f = bwd::asin(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("cosine")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar valExp = std::cos(x.value());
        Scalar gradExp = -std::sin(x.value());

        ADScalar f = bwd::cos(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("arcus cosine")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(0.5);
        Scalar valExp = std::acos(x.value());
        Scalar gradExp = -1 / std::sqrt(1 - x.value() * x.value());

        ADScalar f = bwd::acos(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("tangens")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar valExp = std::tan(x.value());
        Scalar c = std::cos(x.value());
        Scalar gradExp = 1 / (c * c);

        ADScalar f = bwd::tan(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("arcus tangens")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar valExp = std::atan(x.value());
        Scalar gradExp = 1 / (1 + x.value() * x.value());

        ADScalar f = bwd::atan(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("arcus tangens 2")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        ADScalar y(1);
        Scalar valExp = std::atan2(y.value(), x.value());
        Scalar denom = y.value() * y.value() + x.value() * x.value();

        Scalar gradXExp = y.value() / denom;
        Scalar gradyExp = x.value() / denom;

        ADScalar f = bwd::atan2(y, x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradXExp).margin(eps) == derivative(x));
        REQUIRE(Approx(gradyExp).margin(eps) == derivative(y));
    }

    SECTION("square root")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar valExp = std::sqrt(x.value());
        Scalar gradExp = 0.5 / std::sqrt(x.value());

        ADScalar f = bwd::sqrt(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("exponential")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar valExp = std::exp(x.value());
        Scalar gradExp = std::exp(x.value());

        ADScalar f = bwd::exp(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("power")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar valExp = std::pow(x.value(), 2.3);
        Scalar gradExp = 2.3 * std::pow(x.value(), 1.3);

        ADScalar f = bwd::pow(x, 2.3);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("abs")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(-2);
        Scalar valExp = std::abs(x.value());
        Scalar gradExp = 1;

        ADScalar f = bwd::abs(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("abs2")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(-2);
        Scalar valExp = x.value() * x.value();
        Scalar gradExp = 2 * x.value();

        ADScalar f = bwd::abs2(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("log")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar valExp = std::log(x.value());
        Scalar gradExp = 1 / x.value();

        ADScalar f = bwd::log(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("log2")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        Scalar valExp = std::log2(x.value());
        Scalar gradExp = 1 / (x.value() * std::log(2));

        ADScalar f = bwd::log2(x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == derivative(x));
    }

    SECTION("explicit cast")
    {
        ADScalar x1(3);
        Scalar x2 = static_cast<Scalar>(x1);

        REQUIRE(x1.value() == x2);

        x2 = 15;
        x1 = static_cast<ADScalar>(x2);

        REQUIRE(x1.value() == x2);
    }

    SECTION("implicit cast")
    {
        Scalar x2 = 15;
        ADScalar x1 = x2;

        REQUIRE(x1.value() == x2);
    }

    SECTION("equality")
    {
        ADScalar x1(1);
        ADScalar x2(1);
        ADScalar x3(2);

        REQUIRE(x1 == x2);
        REQUIRE(x1 != x3);
    }

    SECTION("less than")
    {
        ADScalar x1(-1);
        ADScalar x2(1);
        ADScalar x3(2);

        REQUIRE(x1 < x2);
        REQUIRE(!(x3 < x2));
    }

    SECTION("less equal than")
    {
        ADScalar x1(1);
        ADScalar x2(1);
        ADScalar x3(2);

        REQUIRE(x1 <= x2);
        REQUIRE(x2 <= x3);
        REQUIRE(!(x3 <= x2));
    }

    SECTION("greater than")
    {
        ADScalar x1(-1);
        ADScalar x2(1);
        ADScalar x3(2);

        REQUIRE(x2 > x1);
        REQUIRE(!(x1 > x2));
    }

    SECTION("greater equal than")
    {
        ADScalar x1(1);
        ADScalar x2(1);
        ADScalar x3(2);

        REQUIRE(x2 >= x1);
        REQUIRE(x3 >= x2);
        REQUIRE(!(x2 >= x3));
    }

    SECTION("multiple variables")
    {
        typename ADScalar::DerivativeMap derivative;
        ADScalar x(3);
        ADScalar y(2);

        Scalar valExp = std::exp(x.value() + y.value() / x.value());
        Scalar gradXExp = (1 - y.value() / (x.value() * x.value())) * valExp;
        Scalar gradYExp = (1 / x.value()) * valExp;

        ADScalar f = bwd::exp(x + y / x);
        f.derivative(derivative);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradXExp).margin(eps) == derivative(x));
        REQUIRE(Approx(gradYExp).margin(eps) == derivative(y));
    }
}
