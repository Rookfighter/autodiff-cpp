/*
 * forward_ad_eigen.h
 *
 *  Created on: 15 Aug 2018
 *      Author: Fabian Meyer
 */

#ifndef ADCPP_FORWARD_AD_EIGEN_H_
#define ADCPP_FORWARD_AD_EIGEN_H_

#include <Eigen/Dense>
#include <functional>
#include "adcpp/forward_ad.h"

namespace Eigen {
    template<> struct NumTraits<fad::Double> : NumTraits<double>
    {
        typedef fad::Double Real;
        typedef fad::Double NonInteger;
        typedef fad::Double Nested;

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

    template<> struct NumTraits<fad::Float> : NumTraits<float>
    {
        typedef fad::Float Real;
        typedef fad::Float NonInteger;
        typedef fad::Float Nested;

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

namespace fad
{
    typedef Eigen::Matrix<Double, -1, 1> VectorXad;
    typedef Eigen::Matrix<Double, -1, -1> MatrixXad;

    typedef Eigen::Matrix<Float, -1, 1> VectorXaf;
    typedef Eigen::Matrix<Float, -1, -1> MatrixXaf;

    class Differentiator
    {
    public:
        typedef std::function<void(const VectorXad&, VectorXad&)> Function;
    private:
        Function func_;
    public:
        Differentiator()
            : func_()
        {}

        Differentiator(const Function &func)
            : func_(func)
        {}

        void setFunction(const Function &func)
        {
            func_ = func;
        }

        void evaluate(const Eigen::VectorXd &inValue,
            Eigen::VectorXd &outValue,
            Eigen::VectorXd &outJacobian)
        {
            VectorXad inFadVec(inValue.size());
            VectorXad outFadVec;

            for(unsigned int i = 0; i < inValue.size(); ++i)
                inFadVec(i).value = inValue(i);

            for(unsigned int i = 0; i < inValue.size(); ++i)
            {
                inFadVec(i).gradient = 1;
                func_(inFadVec, outFadVec);

                if(i == 0)
                {
                    outValue.resize(outFadVec.size());
                    outJacobian.resize(outFadVec.size(), inFadVec.size());

                    for(unsigned int j = 0; j < outFadVec.size(); ++j)
                        outValue(j) = outFadVec(j).value;
                }

                for(unsigned int j = 0; j < outFadVec.size(); ++j)
                    outJacobian(j, i) = outFadVec(j).gradient;

                inFadVec(i).gradient = 0;
            }
        }
    };

}

#endif
