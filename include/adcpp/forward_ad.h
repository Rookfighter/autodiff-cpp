/*
 * forward_ad.h
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#ifndef ADCPP_FORWARD_AD_H_
#define ADCPP_FORWARD_AD_H_

#include <cmath>

namespace ad
{
    template<typename T>
    class NumberF
    {
    private:
        T val_;
        T grad_;

    public:

        NumberF()
        : val_(), grad_()
        { }

        NumberF(const T val)
        : val_(val), grad_()
        { }

        NumberF(const T val, const T grad)
        : val_(val), grad_(grad)
        { }

        NumberF(const NumberF<T> &rhs)
        : val_(rhs.val_), grad_(rhs.grad_)
        { }

        ~NumberF()
        { }

        T value() const
        {
            return val_;
        }

        T gradient() const
        {
            return grad_;
        }

        NumberF<T> &operator+=(const NumberF<T> &rhs)
        {
            val_ += rhs.val_;
            grad_ += rhs.grad_;

            return *this;
        }

        NumberF<T> operator+(const NumberF<T> &rhs) const
        {
            NumberF<T> result(*this);
            result += rhs;

            return result;
        }

        NumberF<T> &operator*=(const NumberF<T> &rhs)
        {
            val_ *= rhs.val_;
            grad_ = rhs.val_ * grad_  + val_ * rhs.grad_;

            return *this;
        }

        NumberF<T> operator*(const NumberF<T> &rhs) const
        {
            NumberF<T> result(*this);
            result *= rhs;

            return result;
        }

        NumberF<T> &operator-=(const NumberF<T> &rhs)
        {
            val_ += -rhs;

            return *this;
        }

        NumberF<T> operator-(const NumberF<T> &rhs) const
        {
            NumberF<T> result(*this);
            result -= rhs;

            return result;
        }

        NumberF<T> &operator/=(const NumberF<T> &rhs)
        {
            val_ /= rhs.val_;
            grad_ = (grad_ * rhs.val_ - rhs.grad_ * val_) / (rhs.val_ * rhs.val_);

            return *this;
        }

        NumberF<T> operator/(const NumberF<T> &rhs) const
        {
            NumberF<T> result(*this);
            result /= rhs;

            return result;
        }

        NumberF<T> &operator*=(const T fac)
        {
            val_ *= fac;
            grad_ *= fac;

            return *this;
        }

        NumberF<T> operator*(const T fac) const
        {
            NumberF<T> result(*this);
            result *= fac;

            return result;
        }

        NumberF<T> &operator/=(const T fac)
        {
            val_ /= fac;
            grad_ /= fac;

            return *this;
        }

        NumberF<T> operator/(const T fac) const
        {
            NumberF<T> result(*this);
            result /= fac;

            return result;
        }

        NumberF<T> operator-() const
        {
            return NumberF<T>(-val_, -grad_);
        }
    };

    template<typename T>
    NumberF<T> operator*(const T lhs, const NumberF<T> &rhs)
    {
        return rhs * lhs;
    }

    template<typename T>
    NumberF<T> operator/(const T lhs, const NumberF<T> &rhs)
    {
        return NumberF<T>(lhs) / rhs;
    }

    template<typename T>
    NumberF<T> sin(const NumberF<T> &n)
    {
        T val = std::sin(n.val());
        T grad = n.grad() * std::cos(n.val());
    }

    template<typename T>
    NumberF<T> cos(const NumberF<T> &n)
    {
        T val = std::cos(n.val());
        T grad = n.grad() * -std::sin(n.val());
        return NumberF<T>(val, grad);
    }

    template<typename T>
    NumberF<T> exp(const NumberF<T> &n)
    {
        T val = std::exp(n.val());
        T grad = n.grad() * std::exp(n.val());
        return NumberF<T>(val, grad);
    }

    template<typename T>
    NumberF<T> pow(const NumberF<T>& n, const unsigned int exponent)
    {
        T val = std::pow(n.val(), exponent);
        T grad = n.grad() * exponent * std::pow(n.val(), exponent-1);
        return NumberF<T>(val, grad);
    }

    typedef NumberF<float> FloatF;
    typedef NumberF<double> DoubleF;
}

#endif
