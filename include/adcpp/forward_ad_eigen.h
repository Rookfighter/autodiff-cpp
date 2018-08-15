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

namespace fad
{
    template<typename T>
    class Evaluator
    {
    public:
        typedef Eigen::Matrix<Number<T>, -1, 1> Vector;
        typedef Eigen::Matrix<Number<T>, -1, -1> Matrix;
        typedef std::function<void(const Vector&, Vector&)> Function;
    private:
        Function func_;
    public:
        Evaluator()
            : func_()
        {}

        Evaluator(const Function &func)
            : func_(func)
        {}

        void setFunction(const Function &func)
        {
            func_ = func;
        }

        void evaluate(const Eigen::VectorXd &inVec,
            Eigen::VectorXd &funcValue,
            Eigen::VectorXd &funcJacobian)
        {
            Vector inFadVec(inVec.size());
            Vector outFadVec;

            for(unsigned int i = 0; i < inVec.size(); ++i)
                inFadVec(i).value = inVec(i);

            for(unsigned int i = 0; i < inVec.size(); ++i)
            {
                inFadVec(i).gradient = 1;
                func_(inFadVec, outFadVec);

                if(i == 0)
                {
                    funcValue.resize(outFadVec.size());
                    funcJacobian.resize(outFadVec.size(), inFadVec.size());

                    for(unsigned int j = 0; j < outFadVec.size(); ++j)
                        funcValue(j) = outFadVec(j).value;
                }

                for(unsigned int j = 0; j < outFadVec.size(); ++j)
                    funcJacobian(j, i) = outFadVec(j).gradient;
            }
        }
    };
}

#endif
