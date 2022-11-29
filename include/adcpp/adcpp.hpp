/* adcpp.hpp
 *
 *  Created on: 21 Aug 2019
 *      Author: Fabian Meyer
 *     License: MIT
 */

#ifndef ADCPP_ADCPP_HPP_
#define ADCPP_ADCPP_HPP_

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
    /// @brief Generic number type for computing derivate in forward mode.
    /// @tparam _Scalar internal scalar type
    template<typename _Scalar>
    class Number
    {
    public:
        using Scalar = _Scalar;

        Number() = default;
        Number(const Number<Scalar> &rhs) = default;
        Number(Number<Scalar> &&rhs) = default;
        ~Number() = default;

        Number(const Scalar value)
            : value_(value)
        { }

        Number(const Scalar value, const Scalar derivative)
            : value_(value), derivative_(derivative)
        { }

        Scalar value() const
        {
            return value_;
        }

        Scalar derivative() const
        {
            return derivative_;
        }

        Number<Scalar> &operator=(const Number<Scalar> &rhs) & = default;
        Number<Scalar> &operator=(Number<Scalar> &&rhs) && = default;

        Number<Scalar> &operator=(const Scalar rhs) &
        {
            value_ = rhs;
            derivative_ = 0;

            return *this;
        }

        Number<Scalar> &operator+=(const Number<Scalar> &rhs)
        {
            value_ += rhs.value_;
            derivative_ += rhs.derivative_;

            return *this;
        }

        Number<Scalar> &operator*=(const Number<Scalar> &rhs)
        {
            derivative_ = rhs.value_ * derivative_  + value_ * rhs.derivative_;
            value_ *= rhs.value_;

            return *this;
        }

        Number<Scalar> &operator-=(const Number<Scalar> &rhs)
        {
            *this += -rhs;
            return *this;
        }

        Number<Scalar> &operator/=(const Number<Scalar> &rhs)
        {
            derivative_ = (derivative_ * rhs.value_ - rhs.derivative_ * value_) / (rhs.value_ * rhs.value_);
            value_ /= rhs.value_;

            return *this;
        }

        Number<Scalar> operator-() const
        {
            return Number<Scalar>(-value_, -derivative_);
        }

        explicit operator Scalar() const
        {
            return value();
        }

    private:
        Scalar value_{0};
        Scalar derivative_{0};
    };

    template<typename Scalar>
    inline Number<Scalar> operator+(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        auto result = lhs;
        result += rhs;
        return result;
    }

    template<typename Scalar>
    inline Number<Scalar> operator-(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        auto result = lhs;
        result -= rhs;
        return result;
    }

    template<typename Scalar>
    inline Number<Scalar> operator/(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        auto result = lhs;
        result /= rhs;
        return result;
    }

    template<typename Scalar>
    inline Number<Scalar> operator*(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        auto result = lhs;
        result *= rhs;
        return result;
    }

    template<typename Scalar>
    inline bool operator==(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        return lhs.value() == rhs.value();
    }

    template<typename Scalar>
    inline bool operator!=(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        return lhs.value() != rhs.value();
    }

    template<typename Scalar>
    inline bool operator<(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        return lhs.value() < rhs.value();
    }

    template<typename Scalar>
    inline bool operator<=(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        return lhs.value() <= rhs.value();
    }

    template<typename Scalar>
    inline bool operator>(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        return lhs.value() > rhs.value();
    }

    template<typename Scalar>
    inline bool operator>=(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        return lhs.value() >= rhs.value();
    }

    template<typename Scalar>
    inline std::ostream& operator<<(std::ostream &lhs, const Number<Scalar> &rhs)
    {
        lhs << '(' << rhs.value() << ',' << rhs.derivative() << ')';
        return lhs;
    }

    template<typename Scalar>
    inline Scalar &operator+=(Scalar &lhs, const Number<Scalar> &rhs)
    {
        lhs += rhs.value();
        return lhs;
    }

    template<typename Scalar>
    inline Number<Scalar> operator+(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return Number<Scalar>(lhs) + rhs;
    }

    template<typename Scalar>
    inline Scalar &operator-=(Scalar &lhs, const Number<Scalar> &rhs)
    {
        lhs -= rhs.value();
        return lhs;
    }

    template<typename Scalar>
    inline Number<Scalar> operator-(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return Number<Scalar>(lhs) - rhs;
    }

    template<typename Scalar>
    inline Scalar &operator*=(Scalar &lhs, const Number<Scalar> &rhs)
    {
        lhs *= rhs.value();
        return lhs;
    }

    template<typename Scalar>
    inline Number<Scalar> operator*(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return Number<Scalar>(lhs) * rhs;
    }

    template<typename Scalar>
    inline Scalar &operator/=(Scalar &lhs, const Number<Scalar> &rhs)
    {
        lhs /= rhs.value();
        return lhs;
    }

    template<typename Scalar>
    inline Number<Scalar> operator/(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return Number<Scalar>(lhs) / rhs;
    }

    template<typename Scalar>
    inline Number<Scalar> sin(const Number<Scalar> &val)
    {
        Scalar value = std::sin(val.value());
        Scalar derivative = val.derivative() * std::cos(val.value());
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> asin(const Number<Scalar> &val)
    {
        Scalar value = std::asin(val.value());
        Scalar derivative = val.derivative() * 1 / std::sqrt(1 - val.value() * val.value());
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> cos(const Number<Scalar> &val)
    {
        Scalar value = std::cos(val.value());
        Scalar derivative = val.derivative() * -std::sin(val.value());
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> acos(const Number<Scalar> &val)
    {
        Scalar value = std::acos(val.value());
        Scalar derivative = val.derivative() * -1 / std::sqrt(1 - val.value() * val.value());
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> tan(const Number<Scalar> &val)
    {
        Scalar value = std::tan(val.value());
        Scalar c = std::cos(val.value());
        Scalar derivative = val.derivative() * 1 / (c * c);
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> atan(const Number<Scalar> &val)
    {
        Scalar value = std::atan(val.value());
        Scalar derivative = val.derivative() * 1 / (1 + val.value() * val.value());

        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> atan2(const Number<Scalar> &y, const Number<Scalar> &x)
    {
        Scalar value = std::atan2(y.value(), x.value());
        Scalar denom = x.value() * x.value() + y.value() * y.value();
        Scalar derivative = x.derivative() * y.value() / denom +
            y.derivative() * x.value() / denom;

        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> exp(const Number<Scalar> &val)
    {
        Scalar value = std::exp(val.value());
        Scalar derivative = val.derivative() * std::exp(val.value());
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> pow(const Number<Scalar> &val, const Scalar exponent)
    {
        Scalar value = std::pow(val.value(), exponent);
        Scalar derivative = val.derivative() * exponent * std::pow(val.value(), exponent - 1);
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> pow(const Number<Scalar> &val, const int exponent)
    {
        Scalar value = std::pow(val.value(), exponent);
        Scalar derivative = val.derivative() * exponent * std::pow(val.value(), exponent - 1);
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> sqrt(const Number<Scalar> &val)
    {
        Scalar value = std::sqrt(val.value());
        Scalar derivative = val.derivative() / (2 * value);
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> conj(const Number<Scalar> &val)
    {
        return val;
    }

    template<typename Scalar>
    inline Number<Scalar> real(const Number<Scalar> &val)
    {
        return val;
    }

    template<typename Scalar>
    inline Number<Scalar> imag(const Number<Scalar> &)
    {
        return Number<Scalar>(0, 0);
    }

    template<typename Scalar>
    inline Number<Scalar> abs(const Number<Scalar> &val)
    {
        return Number<Scalar>(std::abs(val.value()), std::abs(val.derivative()));
    }

    template<typename Scalar>
    inline Number<Scalar> abs2(const Number<Scalar> &val)
    {
        return val * val;
    }

    template<typename Scalar>
    inline Number<Scalar> log(const Number<Scalar> &val)
    {
        Scalar value = std::log(val.value());
        Scalar derivative = val.derivative() * 1 / val.value();
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline Number<Scalar> log2(const Number<Scalar> &val)
    {
        Scalar value = std::log2(val.value());
        Scalar derivative = val.derivative() * 1 / (val.value() * static_cast<Scalar>(0.6931471805599453));
        return Number<Scalar>(value, derivative);
    }

    template<typename Scalar>
    inline bool isfinite(const Number<Scalar> &val)
    {
        return std::isfinite(val.value());
    }

    typedef Number<double> Double;
    typedef Number<float> Float;
}

namespace bwd
{
    template<typename Scalar>
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
            id_ = ss.str();
        }

        virtual ~Expression()
        { }

        virtual Scalar value() const
        {
            return value_;
        }

        virtual void derivative(std::map<std::string, Scalar> &map, const Scalar weight) const = 0;

        const std::string &id() const
        {
            return id_;
        }
    };

    template<typename Scalar>
    class UnaryExpression : public Expression<Scalar>
    {
    protected:
        std::shared_ptr<Expression<Scalar>> expr_;
    public:
        UnaryExpression(const Scalar value,
            const std::shared_ptr<Expression<Scalar>> &expr)
            : Expression<Scalar>(value), expr_(expr)
        { }
    };

    template<typename Scalar>
    class BinaryExpression : public Expression<Scalar>
    {
    protected:
        std::shared_ptr<Expression<Scalar>> lhs_;
        std::shared_ptr<Expression<Scalar>> rhs_;
    public:
        BinaryExpression(const Scalar value,
            const std::shared_ptr<Expression<Scalar>> &lhs,
            const std::shared_ptr<Expression<Scalar>> &rhs)
            : Expression<Scalar>(value), lhs_(lhs), rhs_(rhs)
        { }
    };

    template<typename Scalar>
    class Parameter : public Expression<Scalar>
    {
    public:
        Parameter(const Scalar value)
            : Expression<Scalar>(value)
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            const auto it = map.find(this->id());
            if(it != map.end())
                it->second += weight;
            else
                map[this->id()] = weight;
        }
    };

    template<typename Scalar>
    class Constant : public Expression<Scalar>
    {
    public:
        Constant(const Scalar value)
            : Expression<Scalar>(value)
        { }

        void derivative(std::map<std::string, Scalar> &,
            const Scalar) const override
        { }
    };

    template<typename Scalar>
    class Negate : public UnaryExpression<Scalar>
    {
    public:
        Negate(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(-expr->value(), expr)
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, -weight);
        }
    };

    template<typename Scalar>
    class Sin : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        Sin(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::sin(expr->value()), expr),
            weight_(std::cos(expr->value()))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class ArcSin : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        ArcSin(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::asin(expr->value()), expr),
            weight_(1 / std::sqrt(1 - expr->value() * expr->value()))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class Cos : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        Cos(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::cos(expr->value()), expr),
            weight_(-std::sin(expr->value()))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class ArcCos : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        ArcCos(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::acos(expr->value()), expr),
            weight_(-1 / std::sqrt(1 - expr->value() * expr->value()))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class Tan : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        Tan(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::tan(expr->value()), expr),
            weight_()
        {
            Scalar c = std::cos(expr->value());
            weight_ = 1 / (c * c);
        }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class ArcTan : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        ArcTan(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::atan(expr->value()), expr),
            weight_(1 / (1 + expr->value() * expr->value()))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class ArcTan2 : public BinaryExpression<Scalar>
    {
    private:
        Scalar weightLhs_;
        Scalar weightRhs_;
    public:
        ArcTan2(const std::shared_ptr<Expression<Scalar>> &lhs,
            const std::shared_ptr<Expression<Scalar>> &rhs)
            : BinaryExpression<Scalar>(std::atan2(lhs->value(), rhs->value()), lhs, rhs),
            weightLhs_(), weightRhs_()
        {
            Scalar denom = rhs->value() * rhs->value() + lhs->value() * lhs->value();
            weightLhs_ = rhs->value() / denom;
            weightRhs_ = lhs->value() / denom;
        }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->lhs_->derivative(map, weight * weightLhs_);
            this->rhs_->derivative(map, weight * weightRhs_);
        }
    };

    template<typename Scalar>
    class Exp : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        Exp(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::exp(expr->value()), expr),
            weight_(this->value())
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class Sqrt : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        Sqrt(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::sqrt(expr->value()), expr),
            weight_(1 / (2 * this->value()))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class Abs : public UnaryExpression<Scalar>
    {
    public:
        Abs(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::abs(expr->value()), expr)
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, std::abs(weight));
        }
    };

    template<typename Scalar>
    class Abs2 : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        Abs2(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(expr->value() * expr->value(), expr),
            weight_(2 * expr->value())
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class Log : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        Log(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::log(expr->value()), expr),
            weight_(1 / expr->value())
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class Log2 : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        Log2(const std::shared_ptr<Expression<Scalar>> &expr)
            : UnaryExpression<Scalar>(std::log2(expr->value()), expr),
            weight_(1 / (expr->value() * std::log(Scalar{2})))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class Pow : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        Pow(const std::shared_ptr<Expression<Scalar>> &expr,
            const Scalar exponent)
            : UnaryExpression<Scalar>(std::pow(expr->value(), exponent), expr),
            weight_(exponent * std::pow(expr->value(), exponent - 1))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class PowInt : public UnaryExpression<Scalar>
    {
    private:
        Scalar weight_;
    public:
        PowInt(const std::shared_ptr<Expression<Scalar>> &expr,
            const int exponent)
            : UnaryExpression<Scalar>(std::pow(expr->value(), exponent), expr),
            weight_(exponent * std::pow(expr->value(), exponent - 1))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->expr_->derivative(map, weight * weight_);
        }
    };

    template<typename Scalar>
    class Add : public BinaryExpression<Scalar>
    {
    public:
        Add(const std::shared_ptr<Expression<Scalar>> &lhs,
            const std::shared_ptr<Expression<Scalar>> &rhs)
            : BinaryExpression<Scalar>(lhs->value() + rhs->value(), lhs, rhs)
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->lhs_->derivative(map, weight);
            this->rhs_->derivative(map, weight);
        }
    };

    template<typename Scalar>
    class Subtract : public BinaryExpression<Scalar>
    {
    public:
        Subtract(const std::shared_ptr<Expression<Scalar>> &lhs,
            const std::shared_ptr<Expression<Scalar>> &rhs)
            : BinaryExpression<Scalar>(lhs->value() - rhs->value(), lhs, rhs)
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->lhs_->derivative(map, weight);
            this->rhs_->derivative(map, -weight);
        }
    };

    template<typename Scalar>
    class Multiply : public BinaryExpression<Scalar>
    {
    public:
        Multiply(const std::shared_ptr<Expression<Scalar>> &lhs,
            const std::shared_ptr<Expression<Scalar>> &rhs)
            : BinaryExpression<Scalar>(lhs->value() * rhs->value(), lhs, rhs)
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->lhs_->derivative(map, this->rhs_->value() * weight);
            this->rhs_->derivative(map, this->lhs_->value() * weight);
        }
    };

    template<typename Scalar>
    class Divide : public BinaryExpression<Scalar>
    {
    private:
        Scalar weightLhs_;
        Scalar weightRhs_;
    public:
        Divide(const std::shared_ptr<Expression<Scalar>> &lhs,
            const std::shared_ptr<Expression<Scalar>> &rhs)
            : BinaryExpression<Scalar>(lhs->value() / rhs->value(), lhs, rhs),
            weightLhs_(1 / rhs->value()),
            weightRhs_(-lhs->value() / (rhs->value() * rhs->value()))
        { }

        void derivative(std::map<std::string, Scalar> &map,
            const Scalar weight) const override
        {
            this->lhs_->derivative(map, weightLhs_ * weight);
            this->rhs_->derivative(map, weightRhs_ * weight);
        }
    };

    template<typename _Scalar>
    class Number
    {
    public:
        using Scalar = _Scalar;

        class DerivativeMap
        {
        private:
            std::map<std::string, Scalar> map_;
        public:
            std::map<std::string, Scalar> &map()
            {
                return map_;
            }

            void clear()
            {
                map_.clear();
            }

            bool contains(const Number<Scalar> &value)
            {
                return map_.find(value.id()) != map_.end();
            }

            Scalar operator()(const Number<Scalar> &value) const
            {
                return map_.at(value.id());
            }
        };

        Number()
            : Number(Scalar{0})
        { }

        Number(const Number &rhs) = default;
        Number(Number &&rhs) = default;
        ~Number() = default;

        Number(const Scalar value)
            : Number(std::make_shared<Parameter<Scalar>>(value))
        { }

        Number(const std::shared_ptr<Expression<Scalar>> &expr)
            : expr_(expr)
        { }

        Scalar value() const
        {
            return expr_->value();
        }

        void derivative(DerivativeMap &map) const
        {
            map.clear();
            expr_->derivative(map.map(), 1);
        }

        const std::string &id() const
        {
            return expr_->id();
        }

        const std::shared_ptr<Expression<Scalar>> &expression() const
        {
            return expr_;
        }

        Number<Scalar> &operator=(const Number<Scalar> &rhs) & = default;
        Number<Scalar> &operator=(Number<Scalar> &&rhs) && = default;

        Number<Scalar> &operator=(const Scalar rhs) &
        {
            *this = Number<Scalar>(rhs);
            return *this;
        }

        Number<Scalar> &operator+=(const Scalar rhs)
        {
            *this = *this * rhs;
            return *this;
        }

        Number<Scalar> &operator-=(const Scalar rhs)
        {
            *this = *this - rhs;
            return *this;
        }

        Number<Scalar> &operator*=(const Scalar rhs)
        {
            *this = *this * rhs;
            return *this;
        }

        Number<Scalar> &operator/=(const Scalar rhs)
        {
            *this = *this / rhs;
            return *this;
        }

        Number<Scalar> &operator+=(const Number<Scalar> &rhs)
        {
            *this = *this + rhs;
            return *this;
        }

        Number<Scalar> operator+(const Number<Scalar> &rhs) const
        {
            return Number<Scalar>(std::make_shared<Add<Scalar>>(expr_, rhs.expr_));
        }

        Number<Scalar> &operator-=(const Number<Scalar> &rhs)
        {
            *this = *this - rhs;
            return *this;
        }

        Number<Scalar> operator-(const Number<Scalar> &rhs) const
        {
            return Number<Scalar>(std::make_shared<Subtract<Scalar>>(expr_, rhs.expr_));
        }

        Number<Scalar> &operator*=(const Number<Scalar> &rhs)
        {
            *this = *this * rhs;
            return *this;
        }

        Number<Scalar> operator*(const Number<Scalar> &rhs) const
        {
            return Number<Scalar>(std::make_shared<Multiply<Scalar>>(expr_, rhs.expr_));
        }

        Number<Scalar> &operator/=(const Number<Scalar> &rhs)
        {
            *this = *this / rhs;
            return *this;
        }

        Number<Scalar> operator/(const Number<Scalar> &rhs) const
        {
            return Number<Scalar>(std::make_shared<Divide<Scalar>>(expr_, rhs.expr_));
        }

        Number<Scalar> operator-() const
        {
            return Number<Scalar>(std::make_shared<Negate<Scalar>>(expr_));
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

    private:
        std::shared_ptr<Expression<Scalar>> expr_;
    };

    template<typename Scalar>
    inline Number<Scalar> constant(const Scalar value)
    {
        return Number<Scalar>(std::make_shared<Constant<Scalar>>(value));
    }

    template<typename Scalar>
    inline std::ostream& operator<<(std::ostream &lhs, const Number<Scalar> &rhs)
    {
        lhs << rhs.value();
        return lhs;
    }

    template<typename Scalar>
    inline Number<Scalar> operator+(const Number<Scalar> &lhs, const Scalar rhs)
    {
        return lhs + constant(rhs);
    }

    template<typename Scalar>
    inline Number<Scalar> operator+(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return constant(lhs) + rhs;
    }

    template<typename Scalar>
    inline Number<Scalar> operator-(const Number<Scalar> &lhs, const Scalar rhs)
    {
        return lhs - constant(rhs);
    }

    template<typename Scalar>
    inline Number<Scalar> operator-(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return constant(lhs) - rhs;
    }

    template<typename Scalar>
    inline Number<Scalar> operator*(const Number<Scalar> &lhs, const Scalar rhs)
    {
        return lhs * constant(rhs);
    }

    template<typename Scalar>
    inline Number<Scalar> operator*(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return constant(lhs) * rhs;
    }

    template<typename Scalar>
    inline Number<Scalar> operator/(const Number<Scalar> &lhs, const Scalar rhs)
    {
        return lhs / constant(rhs);
    }

    template<typename Scalar>
    inline Number<Scalar> operator/(const Scalar lhs, const Number<Scalar> &rhs)
    {
        return constant(lhs) / rhs;
    }

    template<typename Scalar>
    inline Number<Scalar> sin(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<Sin<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> asin(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<ArcSin<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> cos(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<Cos<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> acos(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<ArcCos<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> tan(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<Tan<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> atan(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<ArcTan<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> atan2(const Number<Scalar> &lhs, const Number<Scalar> &rhs)
    {
        return Number<Scalar>(std::make_shared<ArcTan2<Scalar>>(lhs.expression(), rhs.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> exp(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<Exp<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> pow(const Number<Scalar> &value, const Scalar exponent)
    {
        return Number<Scalar>(std::make_shared<Pow<Scalar>>(value.expression(), exponent));
    }

    template<typename Scalar>
    inline Number<Scalar> pow(const Number<Scalar> &value, const int exponent)
    {
        return Number<Scalar>(std::make_shared<PowInt<Scalar>>(value.expression(), exponent));
    }

    template<typename Scalar>
    inline Number<Scalar> sqrt(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<Sqrt<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> conj(const Number<Scalar> &value)
    {
        return value;
    }

    template<typename Scalar>
    inline Number<Scalar> real(const Number<Scalar> &value)
    {
        return value;
    }

    template<typename Scalar>
    inline Number<Scalar> imag(const Number<Scalar> &)
    {
        return constant(0);
    }

    template<typename Scalar>
    inline Number<Scalar> abs(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<Abs<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> abs2(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<Abs2<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> log(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<Log<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline Number<Scalar> log2(const Number<Scalar> &value)
    {
        return Number<Scalar>(std::make_shared<Log2<Scalar>>(value.expression()));
    }

    template<typename Scalar>
    inline bool isfinite(const Number<Scalar> &value)
    {
        return std::isfinite(value.value());
    }

    typedef Number<double> Double;
    typedef Number<float> Float;
}
}

#endif
