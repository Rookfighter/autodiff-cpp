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
#include <map>
#include <sstream>

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
    template<typename Scalar, typename T>
    class Expression
    {
    private:
        std::string id_;
        Scalar value_;
    public:
        Expression(const Scalar value)
            : id_(), value_(value)
        {
            std::stringstream ss;
            ss << this;
            id_ = ss.str;
        }

        Scalar value() const
        {
            return value_;
        }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            static_cast<const T&>(*this).gradient(map, weight);
        }

        const std::string &id() const
        {
            return id_;
        }
    };

    template<typename Scalar>
    class Parameter : public Expression<Scalar, Parameter<Scalar>>
    {
    public:
        Parameter(const Scalar value)
            : Expression<Scalar, Parameter<Scalar>>(value)
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            const auto it = map.find(this->id());
            if(it != map.end())
                it->second += weight;
            else
                map[this->id()] = weight;
        }
    };

    template<typename Scalar>
    class Constant : public Expression<Scalar, Constant<Scalar>>
    {
    public:
        Constant(const Scalar value)
            : Expression<Scalar, Constant<Scalar>>(value)
        { }

        void gradient(std::map<std::string, Scalar> &, const Scalar) const
        { }
    };

    template<typename Scalar, typename T>
    class Negate : public Expression<Scalar, Negate<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
    public:
        Negate(const std::shared_ptr<T> expr)
            : Expression<Scalar, Negate<Scalar, T>>(-expr->value()),
            expr_(expr)
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, -weight);
        }
    };

    template<typename Scalar, typename T>
    class Sin : public Expression<Scalar, Sin<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        Sin(const std::shared_ptr<T> expr)
            : Expression<Scalar, Sin<Scalar, T>>(std::sin(expr->value())),
            expr_(expr),
            weight_(std::cos(expr_->value()))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class ArcSin : public Expression<Scalar, ArcSin<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        ArcSin(const std::shared_ptr<T> expr)
            : Expression<Scalar, ArcSin<Scalar, T>>(std::asin(expr->value())),
            expr_(expr),
            weight_(1 / std::sqrt(1 - expr->value() * expr->value()))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class Cos : public Expression<Scalar, Cos<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        Cos(const std::shared_ptr<T> expr)
            : Expression<Scalar, Cos<Scalar, T>>(std::cos(expr->value())),
            expr_(expr),
            weight_(-std::sin(expr_->value()))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class ArcCos : public Expression<Scalar, ArcCos<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        ArcCos(const std::shared_ptr<T> expr)
            : Expression<Scalar, ArcCos<Scalar, T>>(std::acos(expr->value())),
            expr_(expr),
            weight_(-1 / std::sqrt(1 - expr->value() * expr->value()))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class Tan : public Expression<Scalar, Tan<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        Tan(const std::shared_ptr<T> expr)
            : Expression<Scalar, Tan<Scalar, T>>(std::tan(expr->value())),
            expr_(expr),
            weight_()
        {
            Scalar c = std::cos(expr->value());
            weight_ = 1 / (c * c);
        }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class ArcTan : public Expression<Scalar, ArcTan<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        ArcTan(const std::shared_ptr<T> expr)
            : Expression<Scalar, ArcTan<Scalar, T>>(std::atan(expr->value())),
            expr_(expr),
            weight_(1 / (1 + expr->value() * expr->value()))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename L, typename R>
    class ArcTan2 : public Expression<Scalar, ArcTan2<Scalar, L, R>>
    {
    private:
        std::shared_ptr<L> lhs_;
        std::shared_ptr<R> rhs_;
        Scalar weightLhs_;
        Scalar weightRhs_;
    public:
        ArcTan2(const std::shared_ptr<L> lhs, const std::shared_ptr<R> rhs)
            : Expression<Scalar, ArcTan2<Scalar, L, R>>(std::atan2(lhs->value(), rhs->value())),
            lhs_(lhs), rhs_(rhs),
            weightLhs_(), weightRhs_()
        {
            Scalar denom = rhs->value() * rhs.value() + lhs.value() * lhs.value();
            weightLhs_ = rhs->value() / denom;
            weightRhs_ = lhs->value() / denom;
        }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            lhs_->gradient(map, weight * weightLhs_);
            rhs_->gradient(map, weight * weightRhs_);
        }
    };

    template<typename Scalar, typename T>
    class Exp : public Expression<Scalar, Exp<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        Exp(const std::shared_ptr<T> expr)
            : Expression<Scalar, Exp<Scalar, T>>(std::exp(expr->value())),
            expr_(expr),
            weight_(this->value())
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class Sqrt : public Expression<Scalar, Sqrt<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        Sqrt(const std::shared_ptr<T> expr)
            : Expression<Scalar, Sqrt<Scalar, T>>(std::sqrt(expr->value())),
            expr_(expr),
            weight_(1 / (2 * this->value()))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class Abs : public Expression<Scalar, Abs<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
    public:
        Abs(const std::shared_ptr<T> expr)
            : Expression<Scalar, Abs<Scalar, T>>(std::abs(expr->value())),
            expr_(expr)
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, std::abs(weight));
        }
    };

    template<typename Scalar, typename T>
    class Abs2 : public Expression<Scalar, Abs2<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        Abs2(const std::shared_ptr<T> expr)
            : Expression<Scalar, Abs2<Scalar, T>>(expr->value() * expr->value()),
            expr_(expr),
            weight_(expr->value() / 2)
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class Log : public Expression<Scalar, Log<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        Log(const std::shared_ptr<T> expr)
            : Expression<Scalar, Log<Scalar, T>>(std::log(expr->value())),
            expr_(expr),
            weight_(1 / expr->value())
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class Log2 : public Expression<Scalar, Log2<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        Log2(const std::shared_ptr<T> expr)
            : Expression<Scalar, Log2<Scalar, T>>(std::log2(expr->value())),
            expr_(expr),
            weight_(1 / (expr->value() * std::log(2)))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class Pow : public Expression<Scalar, Pow<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        Pow(const std::shared_ptr<T> expr, const Scalar exponent)
            : Expression<Scalar, Pow<Scalar, T>>(std::pow(expr->value(), exponent)),
            expr_(expr),
            weight_(exponent * std::pow(expr->value(), exponent - 1))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename T>
    class PowInt : public Expression<Scalar, PowInt<Scalar, T>>
    {
    private:
        std::shared_ptr<T> expr_;
        Scalar weight_;
    public:
        PowInt(const std::shared_ptr<T> expr, const int exponent)
            : Expression<Scalar, PowInt<Scalar, T>>(std::pow(expr->value(), exponent)),
            expr_(expr),
            weight_(exponent * std::pow(expr->value(), exponent - 1))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            expr_->gradient(map, weight * weight_);
        }
    };

    template<typename Scalar, typename L, typename R>
    class Add : public Expression<Scalar, Add<Scalar, L, R>>
    {
    private:
        std::shared_ptr<L> lhs_;
        std::shared_ptr<R> rhs_;
    public:
        Add(const std::shared_ptr<L> lhs, const std::shared_ptr<R> rhs)
            : Expression<Scalar, Add<Scalar, L, R>>(lhs->value() + rhs->value()),
            lhs_(lhs), rhs_(rhs)
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            lhs_->gradient(map, weight);
            rhs_->gradient(map, weight);
        }
    };

    template<typename Scalar, typename L, typename R>
    class Subtract : public Expression<Scalar, Subtract<Scalar, L, R>>
    {
    private:
        std::shared_ptr<L> lhs_;
        std::shared_ptr<R> rhs_;
    public:
        Subtract(const std::shared_ptr<L> lhs, const std::shared_ptr<R> rhs)
            : Expression<Scalar, Subtract<Scalar, L, R>>(lhs->value() - rhs->value()),
            lhs_(lhs), rhs_(rhs)
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            lhs_->gradient(map, weight);
            rhs_->gradient(map, -weight);
        }
    };

    template<typename Scalar, typename L, typename R>
    class Multiply : public Expression<Scalar, Multiply<Scalar, L, R>>
    {
    private:
        std::shared_ptr<L> lhs_;
        std::shared_ptr<R> rhs_;
    public:
        Multiply(const std::shared_ptr<L> lhs, const std::shared_ptr<R> rhs)
            : Expression<Scalar, Multiply<Scalar, L, R>>(lhs->value() * rhs->value()),
            lhs_(lhs), rhs_(rhs)
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            lhs_->gradient(map, rhs_->value() * weight);
            rhs_->gradient(map, lhs_->value() * weight);
        }
    };

    template<typename Scalar, typename L, typename R>
    class Divide : public Expression<Scalar, Divide<Scalar, L, R>>
    {
    private:
        std::shared_ptr<L> lhs_;
        std::shared_ptr<R> rhs_;
        Scalar weightLhs_;
        Scalar weightRhs_;
    public:
        Divide(const std::shared_ptr<L> lhs, const std::shared_ptr<R> rhs)
            : Expression<Scalar, Divide<Scalar, L, R>>(lhs->value() / rhs->value()),
            lhs_(lhs), rhs_(rhs),
            weightLhs_(1 / rhs->value()),
            weightRhs_(-lhs->value() / (rhs->value() * rhs->value()))
        { }

        void gradient(std::map<std::string, Scalar> &map, const Scalar weight) const
        {
            lhs_->gradient(map, weightLhs_ * weight);
            rhs_->gradient(map, weightRhs_ * weight);
        }
    };

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
                : value(value), children(), gradient(0)
            { }

            Scalar value;
            std::vector<Node> children;
            Scalar gradient;
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
            data_->gradient = grad;
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
            data_ = Data::Ptr(new Data(rhs));
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

    template<typename Scalar>
    bool isfinite(const Number<Scalar> &val)
    {
        return std::isfinite(val.value());
    }

    typedef Number<double> Double;
    typedef Number<float> Float;
}
}

#endif
