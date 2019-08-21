/* adcpp.h
 *
 *  Created on: 21 Aug 2019
 *      Author: Fabian Meyer
 *     License: MIT
 */

#ifndef ADCPP_H_
#define ADCPP_H_

#include <cmath>
#include <memory>
#include <vector>

namespace adcpp
{
namespace fwd
{
    template<typename Scalar>
    class Number
    {
    private:
        Scalar value_;
        Scalar gradient_;
    public:

        Number()
            : value_(0), gradient_(0)
        { }

        Number(const Scalar value)
            : value_(value), gradient_(0)
        { }

        Number(const Scalar value, const Scalar gradient)
            : value_(value), gradient_(gradient)
        { }

        Number(const Number<Scalar> &rhs)
            : value_(rhs.value_), gradient_(rhs.gradient_)
        { }

        ~Number()
        { }

        Scalar value() const
        {
            return value_;
        }

        Scalar gradient() const
        {
            return gradient_;
        }

        Number<Scalar> &operator=(const Number<Scalar> &rhs)
        {
            value_ = rhs.value_;
            gradient_ = rhs.gradient_;

            return *this;
        }

        Number<Scalar> &operator=(const Scalar rhs)
        {
            value_ = rhs;
            gradient_ = 0;

            return *this;
        }

        Number<Scalar> &operator+=(const Number<Scalar> &rhs)
        {
            value_ += rhs.value_;
            gradient_ += rhs.gradient_;

            return *this;
        }

        Number<Scalar> operator+(const Number<Scalar> &rhs) const
        {
            Number<Scalar> result(*this);
            result += rhs;

            return result;
        }

        Number<Scalar> &operator*=(const Number<Scalar> &rhs)
        {
            gradient_ = rhs.value_ * gradient_  + value_ * rhs.gradient_;
            value_ *= rhs.value_;

            return *this;
        }

        Number<Scalar> operator*(const Number<Scalar> &rhs) const
        {
            Number<Scalar> result(*this);
            result *= rhs;

            return result;
        }

        Number<Scalar> &operator-=(const Number<Scalar> &rhs)
        {
            value_ += -rhs;

            return *this;
        }

        Number<Scalar> operator-(const Number<Scalar> &rhs) const
        {
            Number<Scalar> result(*this);
            result -= rhs;

            return result;
        }

        Number<Scalar> &operator/=(const Number<Scalar> &rhs)
        {
            gradient_ = (gradient_ * rhs.value_ - rhs.gradient_ * value_) / (rhs.value_ * rhs.value_);
            value_ /= rhs.value_;

            return *this;
        }

        Number<Scalar> operator/(const Number<Scalar> &rhs) const
        {
            Number<Scalar> result(*this);
            result /= rhs;

            return result;
        }

        Number<Scalar> operator-() const
        {
            return Number<Scalar>(-value_, -gradient_);
        }
    };

    template<typename Scalar>
    Number<Scalar> sin(const Number<Scalar> &val)
    {
        Scalar value = std::sin(val.value());
        Scalar gradient = val.gradient() * std::cos(val.value());
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> asin(const Number<Scalar> &val)
    {
        Scalar value = std::asin(val.value());
        Scalar gradient = val.gradient() * 1 / std::sqrt(1 - val.value() * val.value());
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> cos(const Number<Scalar> &val)
    {
        Scalar value = std::cos(val.value());
        Scalar gradient = val.gradient() * -std::sin(val.value());
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> acos(const Number<Scalar> &val)
    {
        Scalar value = std::acos(val.value());
        Scalar gradient = val.gradient() * -1 / std::sqrt(1 - val.value() * val.value());
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> tan(const Number<Scalar> &val)
    {
        Scalar value = std::tan(val.value());
        Scalar c = std::cos(val.value());
        Scalar gradient = val.gradient() * 1 / (c * c);
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> atan(const Number<Scalar> &val)
    {
        Scalar value = std::atan(val.value());
        Scalar gradient = val.gradient() * 1 / (1 + val.value() * val.value());

        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> atan2(const Number<Scalar> &y, const Number<Scalar> &x)
    {
        Scalar value = std::atan2(y.value(), x.value());
        Scalar denom = x.value() * x.value() + y.value() * y.value();
        Scalar gradient = x.gradient() * y.value() / denom +
            y.gradient() * x.value() / denom;

        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> exp(const Number<Scalar> &val)
    {
        Scalar value = std::exp(val.value());
        Scalar gradient = val.gradient() * std::exp(val.value());
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> pow(const Number<Scalar> &val, const Scalar exponent)
    {
        Scalar value = std::pow(val.value(), exponent);
        Scalar gradient = val.gradient() * exponent * std::pow(val.value(), exponent - 1);
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> pow(const Number<Scalar> &val, const int exponent)
    {
        Scalar value = std::pow(val.value(), exponent);
        Scalar gradient = val.gradient() * exponent * std::pow(val.value(), exponent - 1);
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> sqrt(const Number<Scalar> &val)
    {
        Scalar value = std::sqrt(val.value());
        Scalar gradient = val.gradient() / (2 * value);
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    const Number<Scalar>& conj(const Number<Scalar> &val)
    {
        return val;
    }

    template<typename Scalar>
    const Number<Scalar>& real(const Number<Scalar> &val)
    {
        return val;
    }

    template<typename Scalar>
    Number<Scalar> imag(const Number<Scalar> &val)
    {
        return Number<Scalar>(0, 0);
    }

    template<typename Scalar>
    Number<Scalar> abs(const Number<Scalar> &val)
    {
        return Number<Scalar>(std::abs(val.value()), std::abs(val.gradient()));
    }

    template<typename Scalar>
    Number<Scalar> abs2(const Number<Scalar> &val)
    {
        return val * val;
    }

    typedef Number<double> Double;
    typedef Number<float> Float;
}

namespace bwd
{
    template<typename Scalar>
    class Number
    {
    private:
        struct Node
        {
            Scalar weight;
            Number<Scalar> term;

            Node()
                : Node(0, Number<Scalar>())
            { }

            Node(const Scalar weight, const Number<Scalar> &term)
                : weight(weight), term(term)
            { }

        };

        struct Data
        {
            typedef std::shared_ptr<Data> Ptr;

            Data()
                : Data(0, 0)
            { }

            Data(const Scalar value)
                : Data(value, 0)
            { }

            Data(const Scalar value, const Scalar gradient)
                : value(value), gradient(gradient), children()
            { }

            Scalar value;
            Scalar gradient;
            std::vector<Node> children;
        };

        typename Data::Ptr data_;
    public:
        Number()
            : Number(0, 0)
        { }

        Number(const Scalar value)
            : Number(value, 0)
        { }

        Number(const Scalar value, const Scalar gradient)
        : data_(new Data(value, gradient))
        { }

        Number(const Number<Scalar> &rhs)
        : data_(rhs.data_)
        { }

        ~Number()
        { }

        Number<Scalar> &operator=(const Number<Scalar> &rhs)
        {
            data_ = rhs.data_;

            return *this;
        }

        Number<Scalar> &operator=(const Scalar rhs)
        {
            *this = Number<Scalar>(rhs);
            return *this;
        }

        Number<Scalar> &operator+=(const Number<Scalar> &rhs)
        {
            *this = *this + rhs;
            return *this;
        }

        Number<Scalar> operator+(Number<Scalar> &rhs)
        {
            Number<Scalar> result;

            result.data_->value = data_->value + rhs.data_->value;

            data_->children.push_back({1, result});
            rhs.data_->children.push_back({1, result});

            return result;
        }

        Number<Scalar> &operator*=(Number<Scalar> &rhs)
        {
            *this = *this * rhs;
            return *this;
        }

        Number<Scalar> operator*(Number<Scalar> &rhs)
        {
            Number<Scalar> result;

            result.data_->value = data_->value * rhs.data_->value;

            data_->children.push_back({rhs.data_->value, result});
            rhs.data_->children.push_back({data_->value, result});

            return result;
        }

        Number<Scalar> &operator-=(Number<Scalar> &rhs)
        {
            *this = *this - rhs;
            return *this;
        }

        Number<Scalar> operator-(Number<Scalar> &rhs)
        {
            Number<Scalar> result;

            result.data_->value = data_->value - rhs.data_->value;

            data_->children.push_back({1, result});
            rhs.data_->children.push_back({-1, result});

            return result;
        }

        Number<Scalar> &operator/=(Number<Scalar> &rhs)
        {
            *this = *this / rhs;
            return *this;
        }

        Number<Scalar> operator/(Number<Scalar> &rhs)
        {
            Number<Scalar> result;

            result.data_->value = data_->value / rhs.data_->value;

            Scalar gradLhs = 1 / rhs.data_->value;
            Scalar gradRhs = -data_->value / (rhs.data_->value * rhs.data_->value);

            data_->children.push_back({gradLhs, result});
            rhs.data_->children.push_back({gradRhs, result});

            return result;
        }

        Number<Scalar> operator-()
        {
            Number<Scalar> result;

            result.data_->value = -data_->value;
            data_->children.push_back({-1, result});

            return result;
        }

        Number<Scalar> sin()
        {
            Number<Scalar> result;
            result.data_->value = std::sin(data_->value);

            data_->children.push_back({std::cos(data_->value), result});

            return result;
        }

        Number<Scalar> cos()
        {
            Number<Scalar> result;
            result.data_->value = std::cos(data_->value);

            data_->children.push_back({-std::sin(data_->value), result});

            return result;
        }

        // Number<Scalar> exp() const
        // {
        //     Scalar value = std::exp<Scalar>(value_);
        //     Scalar gradient = gradient_ * std::exp<Scalar>(value_);
        //     return Number<Scalar>(value, gradient);
        // }
        //
        // Number<Scalar> pow(const Scalar exponent) const
        // {
        //     Scalar value = std::pow(value_, exponent);
        //     Scalar gradient = gradient_ * exponent * std::pow(value_, exponent - 1);
        //     return Number<Scalar>(value, gradient);
        // }
        //
        // Number<Scalar> pow(const int exponent) const
        // {
        //     Scalar value = std::pow(value_, exponent);
        //     Scalar gradient = gradient_ * exponent * std::pow(value_, exponent - 1);
        //     return Number<Scalar>(value, gradient);
        // }
        //
        // Number<Scalar> sqrt() const
        // {
        //     Scalar value = std::sqrt(value_);
        //     Scalar gradient = gradient_ / (2 * value);
        //     return Number<Scalar>(value, gradient);
        // }
        //
        // const Number<Scalar>& conj() const
        // {
        //     return *this;
        // }
        //
        // const Number<Scalar>& real() const
        // {
        //     return *this;
        // }
        //
        // Number<Scalar> imag() const
        // {
        //     return Number<Scalar>(0, 0);
        // }
        //
        // Number<Scalar> abs() const
        // {
        //     return Number<Scalar>(std::abs(value_), std::abs(gradient_));
        // }
        //
        // Number<Scalar> abs2() const
        // {
        //     return x * x;
        // }
    };

    typedef Number<double> Double;
    typedef Number<float> Float;
}
}

#endif
