/* adcpp_forward.test.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#include <catch2/catch.hpp>
#include <adcpp/adcpp.hpp>

using namespace adcpp;

TEMPLATE_TEST_CASE("forward algorithmic differentiation", "[forward]", float, double)
{
    using Scalar = TestType;
    using ADScalar = fwd::Number<Scalar>;
    Scalar eps = 1e-6;

    SECTION("construct")
    {
        const auto defaultValue = ADScalar();
        REQUIRE(Scalar{0} == defaultValue.value());
        REQUIRE(Scalar{0} == defaultValue.derivative());

        const auto fromScalar = ADScalar(Scalar{2});
        REQUIRE(Scalar{2} == fromScalar.value());
        REQUIRE(Scalar{0} == fromScalar.derivative());

        const auto fromScalarDerivative = ADScalar(Scalar{3}, Scalar{2});
        REQUIRE(Scalar{3} == fromScalarDerivative.value());
        REQUIRE(Scalar{2} == fromScalarDerivative.derivative());

        const auto copy = ADScalar(fromScalarDerivative);
        REQUIRE(Scalar{3} == copy.value());
        REQUIRE(Scalar{2} == copy.derivative());
        REQUIRE(copy == fromScalarDerivative);
    }

    SECTION("assign")
    {
        auto fromScalar = ADScalar();
        REQUIRE(Scalar{0} == fromScalar.value());
        REQUIRE(Scalar{0} == fromScalar.derivative());

        fromScalar = Scalar{2};
        REQUIRE(Scalar{2} == fromScalar.value());
        REQUIRE(Scalar{0} == fromScalar.derivative());

        auto copy = ADScalar();
        REQUIRE(Scalar{0} == copy.value());
        REQUIRE(Scalar{0} == copy.derivative());

        copy = fromScalar;
        REQUIRE(Scalar{2} == copy.value());
        REQUIRE(Scalar{0} == copy.derivative());
        REQUIRE(copy == fromScalar);
    }

    SECTION("add constant")
    {
        ADScalar x(3, 1);
        Scalar c = 2;

        Scalar valExp = 5;
        Scalar gradExp = 1;

        ADScalar f = ADScalar(c) + x;

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("multiply constant")
    {
        ADScalar x(3, 1);
        Scalar c = 2;

        Scalar valExp = c * x.value();
        Scalar gradExp = c;

        ADScalar f = ADScalar(c) * x;

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("divide constant")
    {
        ADScalar x(3, 1);
        Scalar c = 2;

        Scalar valExp = c / x.value();
        Scalar gradExp = -c / (x.value() * x.value());

        ADScalar f = ADScalar(c) / x;

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("divide by constant")
    {
        ADScalar x(3, 1);
        Scalar c = 2;

        Scalar valExp = x.value() / c;
        Scalar gradExp = 1 / c;

        ADScalar f = x / ADScalar(c);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("sine")
    {
        ADScalar x(3, 1);
        Scalar valExp = std::sin(x.value());
        Scalar gradExp = std::cos(x.value());

        ADScalar f = fwd::sin(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("arcus sine")
    {
        ADScalar x(0.5, 1);
        Scalar valExp = std::asin(x.value());
        Scalar gradExp = 1 / std::sqrt(1 - x.value() * x.value());

        ADScalar f = fwd::asin(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("cosine")
    {
        ADScalar x(3, 1);
        Scalar valExp = std::cos(x.value());
        Scalar gradExp = -std::sin(x.value());

        ADScalar f = fwd::cos(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("arcus cosine")
    {
        ADScalar x(0.5, 1);
        Scalar valExp = std::acos(x.value());
        Scalar gradExp = -1 / std::sqrt(1 - x.value() * x.value());

        ADScalar f = fwd::acos(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("tangens")
    {
        ADScalar x(3, 1);
        Scalar valExp = std::tan(x.value());
        Scalar c = std::cos(x.value());
        Scalar gradExp = 1 / (c * c);

        ADScalar f = fwd::tan(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("arcus tangens")
    {
        ADScalar x(3, 1);
        Scalar valExp = std::atan(x.value());
        Scalar gradExp = 1 / (1 + x.value() * x.value());

        ADScalar f = fwd::atan(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("arcus tangens 2")
    {
        ADScalar x(3, 1);
        ADScalar y(1, 0);
        Scalar valExp = std::atan2(y.value(), x.value());
        Scalar denom = y.value() * y.value() + x.value() * x.value();

        Scalar gradXExp = y.value() / denom;

        ADScalar fx = fwd::atan2(y, x);

        x = ADScalar(3, 0);
        y = ADScalar(1, 1);

        Scalar gradyExp = x.value() / denom;

        ADScalar fy = fwd::atan2(y, x);

        REQUIRE(Approx(valExp).margin(eps) == fx.value());
        REQUIRE(Approx(valExp).margin(eps) == fy.value());
        REQUIRE(Approx(gradXExp).margin(eps) == fx.derivative());
        REQUIRE(Approx(gradyExp).margin(eps) == fy.derivative());
    }

    SECTION("square root")
    {
        ADScalar x(3, 1);
        Scalar valExp = std::sqrt(x.value());
        Scalar gradExp = 0.5 / std::sqrt(x.value());

        ADScalar f = fwd::sqrt(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("exponential")
    {
        ADScalar x(3, 1);
        Scalar valExp = std::exp(x.value());
        Scalar gradExp = std::exp(x.value());

        ADScalar f = fwd::exp(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("power")
    {
        ADScalar x(3, 1);
        Scalar valExp = std::pow(x.value(), static_cast<Scalar>(2.3));
        Scalar gradExp = static_cast<Scalar>(2.3) * std::pow(x.value(), static_cast<Scalar>(1.3));

        ADScalar f = fwd::pow(x, static_cast<Scalar>(2.3));

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("abs")
    {
        ADScalar x(-2, 1);
        Scalar valExp = std::abs(x.value());
        Scalar gradExp = 1;

        ADScalar f = fwd::abs(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("abs2")
    {
        ADScalar x(-2, 1);
        Scalar valExp = x.value() * x.value();
        Scalar gradExp = 2 * x.value();

        ADScalar f = fwd::abs2(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("log")
    {
        ADScalar x(3, 1);
        Scalar valExp = std::log(x.value());
        Scalar gradExp = 1 / x.value();

        ADScalar f = fwd::log(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("log2")
    {
        ADScalar x(3, 1);
        Scalar valExp = std::log2(x.value());
        Scalar gradExp = 1 / (x.value() * std::log(2));

        ADScalar f = fwd::log2(x);

        REQUIRE(Approx(valExp).margin(eps) == f.value());
        REQUIRE(Approx(gradExp).margin(eps) == f.derivative());
    }

    SECTION("explicit cast")
    {
        ADScalar x1(3, 1);
        Scalar x2 = static_cast<Scalar>(x1);

        REQUIRE(x1.value() == x2);

        x2 = 15;
        x1 = static_cast<ADScalar>(x2);

        REQUIRE(x1.value() == x2);
        REQUIRE(x1.derivative() == 0);
    }

    SECTION("implicit cast")
    {
        Scalar x2 = 15;
        ADScalar x1 = x2;

        REQUIRE(x1.value() == x2);
        REQUIRE(x1.derivative() == 0);
    }

    SECTION("equality")
    {
        ADScalar x1(1, 1);
        ADScalar x2(1, 0);
        ADScalar x3(2, 0);

        REQUIRE(x1 == x2);
        REQUIRE(x1 != x3);
    }

    SECTION("less than")
    {
        ADScalar x1(-1, 1);
        ADScalar x2(1, 0);
        ADScalar x3(2, 0);

        REQUIRE(x1 < x2);
        REQUIRE(!(x3 < x2));
    }

    SECTION("less equal than")
    {
        ADScalar x1(1, 1);
        ADScalar x2(1, 0);
        ADScalar x3(2, 0);

        REQUIRE(x1 <= x2);
        REQUIRE(x2 <= x3);
        REQUIRE(!(x3 <= x2));
    }

    SECTION("greater than")
    {
        ADScalar x1(-1, 1);
        ADScalar x2(1, 0);
        ADScalar x3(2, 0);

        REQUIRE(x2 > x1);
        REQUIRE(!(x1 > x2));
    }

    SECTION("greater equal than")
    {
        ADScalar x1(1, 1);
        ADScalar x2(1, 0);
        ADScalar x3(2, 0);

        REQUIRE(x2 >= x1);
        REQUIRE(x3 >= x2);
        REQUIRE(!(x2 >= x3));
    }

    SECTION("multiple variables")
    {
        ADScalar x(3, 1);
        ADScalar y(2, 0);

        Scalar valExp = std::exp(x.value() + y.value() / x.value());

        Scalar gradXExp = (1 - y.value() / (x.value() * x.value())) * valExp;
        ADScalar fx = fwd::exp(x + y / x);

        x = ADScalar(3, 0);
        y = ADScalar(2, 1);
        Scalar gradYExp = (1 / x.value()) * valExp;
        ADScalar fy = fwd::exp(x + y / x);

        REQUIRE(Approx(valExp).margin(eps) == fx.value());
        REQUIRE(Approx(valExp).margin(eps) == fy.value());
        REQUIRE(Approx(gradXExp).margin(eps) == fx.derivative());
        REQUIRE(Approx(gradYExp).margin(eps) == fy.derivative());
    }
}
