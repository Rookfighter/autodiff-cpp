/*
 * FowardAD.hpp
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#ifndef FORWARD_AD_HPP_
#define FORWARD_AD_HPP_

#include <cmath>

namespace fad
{
    template<typename T>
    class Num
    {
    private:
        T val_;
        T jac_;

    public:

        Num()
        : val_(), jac_()
        { }

        Num(const T val, const T jac)
        : val_(val), jac_(jac)
        { }

        Num(const Num<T> &rhs)
        : val_(rhs.val_), jac_(rhs.jac_)
        { }

        ~Num()
        { }

        T val() const
        {
            return val_;
        }

        T jac() const
        {
            return jac_;
        }

        Num<T> &operator+=(const Num<T> &rhs)
        {
            val_ += rhs.val_;
            jac_ += rhs.jac_;

            return *this;
        }

        Num<T> operator+(const Num<T> &rhs) const
        {
            Num<T> result(*this);
            result += rhs;

            return result;
        }

        Num<T> &operator*=(const Num<T> &rhs)
        {
            val_ *= rhs.val_;
            jac_ = rhs.val_ * jac_  + val_ * rhs.jac_;

            return *this;
        }

        Num<T> operator*(const Num<T> &rhs) const
        {
            Num<T> result(*this);
            result *= rhs;

            return result;
        }

        Num<T> &operator-=(const Num<T> &rhs)
        {
            val_ += -rhs;

            return *this;
        }

        Num<T> operator-(const Num<T> &rhs) const
        {
            Num<T> result(*this);
            result -= rhs;

            return result;
        }

        Num<T> &operator/=(const Num<T> &rhs)
        {
            val_ /= rhs.val_;
            jac_ = (jac_ * rhs.val_ - rhs.jac_ * val_) / (rhs.val_ * rhs.val_);

            return *this;
        }

        Num<T> operator/(const Num<T> &rhs) const
        {
            Num<T> result(*this);
            result /= rhs;

            return result;
        }

        Num<T> &operator*=(const T fac)
        {
            val_ *= fac;
            jac_ *= fac;

            return *this;
        }

        Num<T> operator*(const T fac) const
        {
            Num<T> result(*this);
            result *= fac;

            return result;
        }

        Num<T> &operator/=(const T fac)
        {
            val_ /= fac;
            jac_ /= fac;

            return *this;
        }

        Num<T> operator/(const T fac) const
        {
            Num<T> result(*this);
            result /= fac;

            return result;
        }

        Num<T> operator-() const
        {
            return Num<T>(-val_, -jac_);
        }
    };

    template<typename T>
    Num<T> operator*(const T lhs, const Num<T> &rhs)
    {
        return rhs * lhs;
    }

    template<typename T>
    Num<T> sin(const Num<T> &n)
    {
        T val = std::sin(n.val());
        T jac = n.jac() * std::cos(n.val());
    }

    template<typename T>
    Num<T> cos(const Num<T> &n)
    {
        T val = std::cos(n.val());
        T jac = n.jac() * -std::sin(n.val());
        return Num<T>(val, jac);
    }

    template<typename T>
    Num<T> exp(const Num<T> &n)
    {
        T val = std::exp(n.val());
        T jac = n.jac() * std::exp(n.val());
        return Num<T>(val, jac);
    }

    template<typename T>
    Num<T> pow(const Num<T>& n, const unsigned int exponent)
    {
        T val = std::pow(n.val(), exponent);
        T jac = n.jac() * exponent * std::pow(n.val(), exponent-1);
        return Num<T>(val, jac);
    }

    typedef Num<float> Float;
    typedef Num<double> Double;
}

#endif
