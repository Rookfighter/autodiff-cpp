/* adcpp_eigen.h
 *
 *  Created on: 21 Aug 2019
 *      Author: Fabian Meyer
 *     License: MIT
 */

#ifndef ADCPP_EIGEN_H_
#define ADCPP_EIGEN_H_

#include <adcpp.h>
#include <Eigen/Core>

namespace Eigen {
    template<> struct NumTraits<adcpp::fwd::Double>
        : NumTraits<double>
    {
        typedef adcpp::fwd::Double Real;
        typedef adcpp::fwd::Double NonInteger;
        typedef adcpp::fwd::Double Nested;
        enum {
            IsComplex = 0,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 1,
            AddCost = 3,
            MulCost = 3
        };
    };

    template<> struct NumTraits<adcpp::fwd::Float>
        : NumTraits<float>
    {
        typedef adcpp::fwd::Float Real;
        typedef adcpp::fwd::Float NonInteger;
        typedef adcpp::fwd::Float Nested;
        enum {
            IsComplex = 0,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 1,
            AddCost = 3,
            MulCost = 3
        };
    };

    template<> struct NumTraits<adcpp::bwd::Double>
        : NumTraits<double>
    {
        typedef adcpp::bwd::Double Real;
        typedef adcpp::bwd::Double NonInteger;
        typedef adcpp::bwd::Double Nested;
        enum {
            IsComplex = 0,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 1,
            AddCost = 3,
            MulCost = 3
        };
    };

    template<> struct NumTraits<adcpp::bwd::Float>
        : NumTraits<float>
    {
        typedef adcpp::bwd::Float Real;
        typedef adcpp::bwd::Float NonInteger;
        typedef adcpp::bwd::Float Nested;
        enum {
            IsComplex = 0,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 1,
            AddCost = 3,
            MulCost = 3
        };
    };
}

namespace adcpp
{
namespace fwd
{
    typedef Eigen::Matrix<Double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
    typedef Eigen::Matrix<Double, 2, 2> Matrix2d;
    typedef Eigen::Matrix<Double, 3, 3> Matrix3d;
    typedef Eigen::Matrix<Double, 4, 4> Matrix4d;
    typedef Eigen::Matrix<Double, 5, 5> Matrix5d;

    typedef Eigen::Matrix<Double, Eigen::Dynamic, 1> VectorXd;
    typedef Eigen::Matrix<Double, 2, 1> Vector2d;
    typedef Eigen::Matrix<Double, 3, 1> Vector3d;
    typedef Eigen::Matrix<Double, 4, 1> Vector4d;
    typedef Eigen::Matrix<Double, 5, 1> Vector5d;

    typedef Eigen::Matrix<Float, Eigen::Dynamic, Eigen::Dynamic> MatrixXf;
    typedef Eigen::Matrix<Float, 2, 2> Matrix2f;
    typedef Eigen::Matrix<Float, 3, 3> Matrix3f;
    typedef Eigen::Matrix<Float, 4, 4> Matrix4f;
    typedef Eigen::Matrix<Float, 5, 5> Matrix5f;

    typedef Eigen::Matrix<Float, Eigen::Dynamic, 1> VectorXf;
    typedef Eigen::Matrix<Float, 2, 1> Vector2f;
    typedef Eigen::Matrix<Float, 3, 1> Vector3f;
    typedef Eigen::Matrix<Float, 4, 1> Vector4f;
    typedef Eigen::Matrix<Float, 5, 1> Vector5f;
}

namespace bwd
{
    typedef Eigen::Matrix<Double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
    typedef Eigen::Matrix<Double, 2, 2> Matrix2d;
    typedef Eigen::Matrix<Double, 3, 3> Matrix3d;
    typedef Eigen::Matrix<Double, 4, 4> Matrix4d;
    typedef Eigen::Matrix<Double, 5, 5> Matrix5d;

    typedef Eigen::Matrix<Double, Eigen::Dynamic, 1> VectorXd;
    typedef Eigen::Matrix<Double, 2, 1> Vector2d;
    typedef Eigen::Matrix<Double, 3, 1> Vector3d;
    typedef Eigen::Matrix<Double, 4, 1> Vector4d;
    typedef Eigen::Matrix<Double, 5, 1> Vector5d;

    typedef Eigen::Matrix<Float, Eigen::Dynamic, Eigen::Dynamic> MatrixXf;
    typedef Eigen::Matrix<Float, 2, 2> Matrix2f;
    typedef Eigen::Matrix<Float, 3, 3> Matrix3f;
    typedef Eigen::Matrix<Float, 4, 4> Matrix4f;
    typedef Eigen::Matrix<Float, 5, 5> Matrix5f;

    typedef Eigen::Matrix<Float, Eigen::Dynamic, 1> VectorXf;
    typedef Eigen::Matrix<Float, 2, 1> Vector2f;
    typedef Eigen::Matrix<Float, 3, 1> Vector3f;
    typedef Eigen::Matrix<Float, 4, 1> Vector4f;
    typedef Eigen::Matrix<Float, 5, 1> Vector5f;

    template<typename Scalar, typename DerivedA, typename DerivedB>
    inline void gradient(const Eigen::MatrixBase<DerivedA> &x,
        const Number<Scalar> &f,
        Eigen::MatrixBase<DerivedB> &grad)
    {
        assert(grad.size() == x.size());

        typename bwd::Number<Scalar>::DerivativeMap derivative;
        f.derivative(derivative);

        grad.setZero();
        for(long int i = 0; i < x.size(); ++i)
        {
            if(derivative.contains(x(i)))
                grad(i) = derivative(x(i));
        }
    }

    template<typename DerivedA, typename DerivedB, typename DerivedC>
    inline void jacobian(const Eigen::MatrixBase<DerivedA> &x,
        const Eigen::MatrixBase<DerivedB> &f,
        Eigen::MatrixBase<DerivedC> &jac)
    {
        assert(jac.rows() == f.size());
        assert(jac.cols() == x.size());

        typename Eigen::MatrixBase<DerivedB>::Scalar::DerivativeMap derivative;
        jac.setZero();
        for(long int i = 0; i < f.size(); ++i)
        {
            f(i).derivative(derivative);
            for(long int j = 0; j < x.size(); ++j)
            {
                if(derivative.contains(x(j)))
                    jac(i, j) = derivative(x(j));
            }
        }
    }
}
}

#endif
