/*
 * forward_ad.h
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#ifndef ADCPP_FORWARD_AD_H_
#define ADCPP_FORWARD_AD_H_

#include <cmath>

namespace fad
{
    template<typename T>
    class Number
    {
    public:
        T value;
        T gradient;

        Number()
        : value(0), gradient(0)
        { }

        Number(const T val)
        : value(val), gradient(0)
        { }

        Number(const T val, const T grad)
        : value(val), gradient(grad)
        { }

        Number(const Number<T> &rhs)
        : value(rhs.value), gradient(rhs.gradient)
        { }

        ~Number()
        { }

        Number<T> &operator=(const Number<T> &rhs)
        {
            value = rhs.value;
            gradient = rhs.gradient;

            return *this;
        }

        Number<T> &operator=(const T rhs)
        {
            value = rhs;
            gradient = 0;

            return *this;
        }

        Number<T> &operator+=(const Number<T> &rhs)
        {
            value += rhs.value;
            gradient += rhs.gradient;

            return *this;
        }

        Number<T> operator+(const Number<T> &rhs) const
        {
            Number<T> result(*this);
            result += rhs;

            return result;
        }

        Number<T> &operator*=(const Number<T> &rhs)
        {
            value *= rhs.value;
            gradient = rhs.value * gradient  + value * rhs.gradient;

            return *this;
        }

        Number<T> operator*(const Number<T> &rhs) const
        {
            Number<T> result(*this);
            result *= rhs;

            return result;
        }

        Number<T> &operator-=(const Number<T> &rhs)
        {
            value += -rhs;

            return *this;
        }

        Number<T> operator-(const Number<T> &rhs) const
        {
            Number<T> result(*this);
            result -= rhs;

            return result;
        }

        Number<T> &operator/=(const Number<T> &rhs)
        {
            value /= rhs.value;
            gradient = (gradient * rhs.value - rhs.gradient * value) / (rhs.value * rhs.value);

            return *this;
        }

        Number<T> operator/(const Number<T> &rhs) const
        {
            Number<T> result(*this);
            result /= rhs;

            return result;
        }

        Number<T> &operator*=(const T fac)
        {
            value *= fac;
            gradient *= fac;

            return *this;
        }

        Number<T> operator*(const T fac) const
        {
            Number<T> result(*this);
            result *= fac;

            return result;
        }

        Number<T> &operator/=(const T fac)
        {
            value /= fac;
            gradient /= fac;

            return *this;
        }

        Number<T> operator/(const T fac) const
        {
            Number<T> result(*this);
            result /= fac;

            return result;
        }

        Number<T> operator-() const
        {
            return Number<T>(-value, -gradient);
        }
    };

    template<typename T>
    Number<T> operator-(const T lhs, const Number<T> &rhs)
    {
        return lhs + (-rhs);
    }

    template<typename T>
    Number<T> operator+(const T lhs, const Number<T> &rhs)
    {
        return rhs + lhs;
    }

    template<typename T>
    Number<T> operator*(const T lhs, const Number<T> &rhs)
    {
        return rhs * lhs;
    }

    template<typename T>
    Number<T> operator/(const T lhs, const Number<T> &rhs)
    {
        return Number<T>(lhs) / rhs;
    }

    template<typename T>
    Number<T> sin(const Number<T> &n)
    {
        T val = std::sin(n.value);
        T grad = n.gradient * std::cos(n.value);
        return Number<T>(val, grad);
    }

    template<typename T>
    Number<T> cos(const Number<T> &n)
    {
        T val = std::cos(n.value);
        T grad = n.gradient * -std::sin(n.value);
        return Number<T>(val, grad);
    }

    template<typename T>
    Number<T> exp(const Number<T> &n)
    {
        T val = std::exp(n.value);
        T grad = n.gradient * std::exp(n.value);
        return Number<T>(val, grad);
    }

    template<typename T>
    Number<T> pow(const Number<T>& n, const unsigned int exponent)
    {
        T val = std::pow(n.value, exponent);
        T grad = n.gradient * exponent * std::pow(n.value, exponent-1);
        return Number<T>(val, grad);
    }

    template<typename T>
    Number<T> sqrt(const Number<T>& n)
    {
        T val = std::sqrt(n.value);
        T grad = n.gradient / (2 * val);
        return Number<T>(val, grad);
    }

    template<typename T>
    const Number<T>& conj(const Number<T>& x)  { return x; }
    template<typename T>
    const Number<T>& real(const Number<T>& x)  { return x; }
    template<typename T>
    Number<T> imag(const Number<T>&)    { return Number<T>(); }
    template<typename T>
    Number<T> abs(const Number<T>&  x)  { return Number<T>(std::abs(x.value), std::abs(x.value)); }
    template<typename T>
    Number<T> abs2(const Number<T>& x)  { return x * x; }

    #define FAD_INSTANTIATE(t,n)                                            \
        typedef Number<t> n;                                                \
        inline n operator-(const t lhs, const n &rhs)                       \
        { return operator-<t>(lhs, rhs); }                                  \
        inline n operator+(const t lhs, const n &rhs)                       \
        { return operator+<t>(lhs, rhs); }                                  \
        inline n operator*(const t lhs, const n &rhs)                       \
        { return operator*<t>(lhs, rhs); }                                  \
        inline n operator/(const t lhs, const n &rhs)                       \
        { return operator/<t>(lhs, rhs); }                                  \
        inline n sin(const n& x) { return sin<t>(x); }                      \
        inline n cos(const n& x) { return cos<t>(x); }                      \
        inline n exp(const n& x) { return exp<t>(x); }                      \
        inline n pow(const n& x, const unsigned int exponent)               \
        { return pow<t>(x, exponent); }                                     \
        inline n sqrt(const n& x) { return sqrt<t>(x); }                    \
        inline const n& conj(const n& x)  { return conj<t>(x); }            \
        inline const n& real(const n& x)  { return real<t>(x); }            \
        inline n imag(const n& x)  { return imag<t>(x); }                   \
        inline n abs(const n& x)  { return abs<t>(x); }                     \
        inline n abs2(const n& x)  { return abs2<t>(x); }


    FAD_INSTANTIATE(double, Double)
    FAD_INSTANTIATE(float, Float)
}

#endif
