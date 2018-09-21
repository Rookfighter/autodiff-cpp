/*
 * forward_ad_eigen.cpp
 *
 *  Created on: 17 Feb 2018
 *      Author: Fabian Meyer
 */

#include <catch.hpp>
#include "adcpp/forward_ad_eigen.h"
#include "eigen_assert.h"

using namespace fad;

TEST_CASE("Eigen forward algorithmic differentiation")
{
    double eps = 1e-6;

    SECTION("add constant")
    {
        // Eigen::VectorXd x(3);
        // x << 1, 2, 3;
        // Eigen::VectorXd c(3);
        // c << 2, 3, -1;
        // Eigen::VectorXd expValue(3);
        // expValue << 3, 5, 2;
        // Eigen::MatrixXd expJacobian(3,3);
        // expJacobian << 1, 0, 0,
        //                0, 1, 0,
        //                0, 0, 1;
        //
        // Eigen::VectorXd actValue(3);
        // Eigen::MatrixXd actJacobian(3,3);
        //
        // diff.setFunction([c](const DiffD::Vector &x){return c + x});
        // diff.evaluate(x, actValue, actJacobian);
        //
        // REQUIRE_MAT(expValue, actValue, eps);
        // REQUIRE_MAT(expJacobian, actJacobian, eps);
    }
}
