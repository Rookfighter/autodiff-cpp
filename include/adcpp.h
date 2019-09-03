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
#include <ostream>

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

        bool operator==(const Number<Scalar> &rhs) const
        {
            return value() == rhs.value();
        }

        bool operator!=(const Number<Scalar> &rhs) const
        {
            return value() != rhs.value();
        }

        bool operator<(const Number<Scalar> &rhs) const
        {
            return value() < rhs.value();
        }

        bool operator<=(const Number<Scalar> &rhs) const
        {
            return value() <= rhs.value();
        }

        bool operator>(const Number<Scalar> &rhs) const
        {
            return value() > rhs.value();
        }

        bool operator>=(const Number<Scalar> &rhs) const
        {
            return value() >= rhs.value();
        }

        explicit operator Scalar() const
        {
            return value();
        }

    };

    template<typename Scalar>
    std::ostream& operator<<(std::ostream &lhs, const Number<Scalar> &rhs)
    {
        lhs << '(' << rhs.value() << ',' << rhs.gradient() << ')';

        return lhs;
    }

    template<typename Scalar>
    Scalar &operator+=(Scalar &lhs, const Number<Scalar> &rhs)
    {
        lhs += rhs.value();
        return lhs;
    }

    template<typename Scalar>
    Number<Scalar> operator+(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return Number<Scalar>(lhs) + rhs;
    }

    template<typename Scalar>
    Scalar &operator-=(Scalar &lhs, const Number<Scalar> &rhs)
    {
        lhs -= rhs.value();
        return lhs;
    }

    template<typename Scalar>
    Number<Scalar> operator-(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return Number<Scalar>(lhs) - rhs;
    }

    template<typename Scalar>
    Scalar &operator*=(Scalar &lhs, const Number<Scalar> &rhs)
    {
        lhs *= rhs.value();
        return lhs;
    }

    template<typename Scalar>
    Number<Scalar> operator*(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return Number<Scalar>(lhs) * rhs;
    }

    template<typename Scalar>
    Scalar &operator/=(Scalar &lhs, const Number<Scalar> &rhs)
    {
        lhs /= rhs.value();
        return lhs;
    }

    template<typename Scalar>
    Number<Scalar> operator/(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return Number<Scalar>(lhs) / rhs;
    }

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

    template<typename Scalar>
    Number<Scalar> log(const Number<Scalar> &val)
    {
        Scalar value = std::log(val.value());
        Scalar gradient = val.gradient() * 1 / val.value();
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    Number<Scalar> log2(const Number<Scalar> &val)
    {
        Scalar value = std::log2(val.value());
        Scalar gradient = val.gradient() * 1 / (val.value() * 0.6931471805599453);
        return Number<Scalar>(value, gradient);
    }

    template<typename Scalar>
    bool isfinite(const Number<Scalar> &val)
    {
        return std::isfinite(val.value());
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
            Number<Scalar> var;

            Node()
                : Node(0, Number<Scalar>())
            { }

            Node(const Scalar weight, const Number<Scalar> &var)
                : weight(weight), var(var)
            { }

        };

        struct Data
        {
            typedef std::shared_ptr<Data> Ptr;

            Data()
                : Data(0)
            { }

            Data(const Scalar value)
                : value(value), children(), gradient(0), fixedGradient(false)
            { }

            Scalar value;
            std::vector<Node> children;
            Scalar gradient;
            bool fixedGradient;
        };

        typename Data::Ptr data_;
    public:
        Number()
            : Number(0)
        { }

        Number(const Scalar value)
        : data_(new Data(value))
        { }

        Number(const Number<Scalar> &rhs)
        : data_(rhs.data_)
        { }

        ~Number()
        { }

        Scalar value() const
        {
            return data_->value;
        }

        Scalar gradient() const
        {
            if(data_->gradient != 0)
                return data_->gradient;

            Scalar grad = 0;
            for(size_t i = 0; i < data_->children.size(); ++i)
                grad += data_->children[i].weight * data_->children[i].var.gradient();

            return grad;
        }

        void setGradient(const Scalar grad)
        {
            data_->fixedGradient = true;
            data_->gradient = grad;
        }

        void unsetGradient()
        {
            data_->fixedGradient = false;
            data_->gradient = 0;
        }

        void addChild(const Scalar weight, const Number<Scalar> &val) const
        {
            data_->children.push_back({weight, val});
        }

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

        Number<Scalar> operator+(const Number<Scalar> &rhs) const
        {
            Number<Scalar> result;

            result.data_->value = data_->value + rhs.data_->value;

            addChild(1, result);
            rhs.addChild(1, result);

            return result;
        }

        Number<Scalar> &operator*=(const Number<Scalar> &rhs)
        {
            *this = *this * rhs;
            return *this;
        }

        Number<Scalar> operator*(const Number<Scalar> &rhs) const
        {
            Number<Scalar> result;

            result.data_->value = data_->value * rhs.data_->value;

            addChild(rhs.data_->value, result);
            rhs.addChild(data_->value, result);

            return result;
        }

        Number<Scalar> &operator-=(const Number<Scalar> &rhs)
        {
            *this = *this - rhs;
            return *this;
        }

        Number<Scalar> operator-(const Number<Scalar> &rhs) const
        {
            Number<Scalar> result;

            result.data_->value = data_->value - rhs.data_->value;

            addChild(1, result);
            rhs.addChild(-1, result);

            return result;
        }

        Number<Scalar> &operator/=(const Number<Scalar> &rhs)
        {
            *this = *this / rhs;
            return *this;
        }

        Number<Scalar> operator/(const Number<Scalar> &rhs) const
        {
            Number<Scalar> result;

            result.data_->value = data_->value / rhs.data_->value;

            Scalar gradLhs = 1 / rhs.data_->value;
            Scalar gradRhs = -data_->value / (rhs.data_->value * rhs.data_->value);

            addChild(gradLhs, result);
            rhs.addChild(gradRhs, result);

            return result;
        }

        Number<Scalar> operator-() const
        {
            Number<Scalar> result;

            result.data_->value = -data_->value;
            addChild(-1, result);

            return result;
        }

        bool operator==(const Number<Scalar> &rhs) const
        {
            return value() == rhs.value();
        }

        bool operator!=(const Number<Scalar> &rhs) const
        {
            return value() != rhs.value();
        }

        bool operator<(const Number<Scalar> &rhs) const
        {
            return value() < rhs.value();
        }

        bool operator<=(const Number<Scalar> &rhs) const
        {
            return value() <= rhs.value();
        }

        bool operator>(const Number<Scalar> &rhs) const
        {
            return value() > rhs.value();
        }

        bool operator>=(const Number<Scalar> &rhs) const
        {
            return value() >= rhs.value();
        }

        explicit operator Scalar() const
        {
            return value();
        }
    };

    template<typename Scalar>
    std::ostream& operator<<(std::ostream &lhs, const Number<Scalar> &rhs)
    {
        lhs << rhs.value();
        return lhs;
    }

    template<typename Scalar>
    Number<Scalar> sin(const Number<Scalar> &val)
    {
        Scalar value = std::sin(val.value());
        Scalar gradient = std::cos(val.value());

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> asin(const Number<Scalar> &val)
    {
        Scalar value = std::asin(val.value());
        Scalar gradient = 1 / std::sqrt(1 - val.value() * val.value());

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> cos(const Number<Scalar> &val)
    {
        Scalar value = std::cos(val.value());
        Scalar gradient = -std::sin(val.value());

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> acos(const Number<Scalar> &val)
    {
        Scalar value = std::acos(val.value());
        Scalar gradient = -1 / std::sqrt(1 - val.value() * val.value());

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> tan(const Number<Scalar> &val)
    {
        Scalar value = std::tan(val.value());
        Scalar c = std::cos(val.value());
        Scalar gradient = 1 / (c * c);

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> atan(const Number<Scalar> &val)
    {
        Scalar value = std::atan(val.value());
        Scalar gradient = 1 / (1 + val.value() * val.value());

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> atan2(const Number<Scalar> &y, const Number<Scalar> &x)
    {
        Scalar value = std::atan2(y.value(), x.value());
        Scalar denom = x.value() * x.value() + y.value() * y.value();
        Scalar gradRhs = y.value() / denom;
        Scalar gradLhs = x.value() / denom;

        Number<Scalar> result(value);

        x.addChild(gradRhs, result);
        y.addChild(gradLhs, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> exp(const Number<Scalar> &val)
    {
        Scalar value = std::exp(val.value());
        Scalar gradient = std::exp(val.value());

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> pow(const Number<Scalar> &val, const Scalar exponent)
    {
        Scalar value = std::pow(val.value(), exponent);
        Scalar gradient = exponent * std::pow(val.value(), exponent - 1);

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> pow(const Number<Scalar> &val, const int exponent)
    {
        Scalar value = std::pow(val.value(), exponent);
        Scalar gradient = exponent * std::pow(val.value(), exponent - 1);

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> sqrt(const Number<Scalar> &val)
    {
        Scalar value = std::sqrt(val.value());
        Scalar gradient = 1 / (2 * value);

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
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
        Number<Scalar> result(0);
        val.addChild(0, result);
        return result;
    }

    template<typename Scalar>
    Number<Scalar> abs(const Number<Scalar> &val)
    {
        Scalar value = std::abs(val.value());
        Scalar gradient = 1;

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> abs2(const Number<Scalar> &val)
    {
        return val * val;
    }

    template<typename Scalar>
    Number<Scalar> log(const Number<Scalar> &val)
    {
        Scalar value = std::log(val.value());
        Scalar gradient = 1 / val.value();

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    template<typename Scalar>
    Number<Scalar> log2(const Number<Scalar> &val)
    {
        Scalar value = std::log2(val.value());
        Scalar gradient = 1 / (val.value() * std::log(2));

        Number<Scalar> result(value);

        val.addChild(gradient, result);

        return result;
    }

    typedef Number<double> Double;
    typedef Number<float> Float;
}
}

#endif
