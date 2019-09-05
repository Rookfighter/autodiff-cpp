/* adcpp_eigen_backward.cpp
 *
 *  Created on: 21 Aug 2019
 *      Author: Fabian Meyer
 */

#include <catch2/catch.hpp>
#include <adcpp_eigen.h>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>
#include "assert/eigen_require.h"
#include <iostream>

using namespace adcpp;

TEST_CASE("Eigen backward algorithmic differentiation")
{
    double eps = 1e-6;

    SECTION("exp")
    {
        bwd::Vector2d x;
        x << 3, 2;

        Eigen::Vector2d valExp;
        valExp <<
            std::exp(x(0).value()),std::exp(x(1).value());
        Eigen::Matrix2d jacExp;
        jacExp << std::exp(x(0).value()), 0,
            0, std::exp(x(1).value());

        bwd::Vector2d f = x.array().exp();

        Eigen::Matrix2d jacAct;
        bwd::jacobian(x, f, jacAct);

        REQUIRE_MATRIX_APPROX(valExp, f.template cast<double>(), eps);
        REQUIRE_MATRIX_APPROX(jacExp, jacAct, eps);
    }

    // SECTION("singular value decomposition")
    // {
    //     std::cout << "SVD START" << std::endl;
    //     bwd::Matrix4d A;
    //     A << 2, 3, 11, 5,
    //         1, 1, 5, 2,
    //         2, 1, -3, 2,
    //         1, 1, -3, 4;
    //     bwd::Vector4d b;
    //     b << 2, 1, -3, -3;
    //
    //     bwd::Vector4d resultAct;
    //     Eigen::Vector4d valExp;
    //     Eigen::Vector4d gradExp;
    //     valExp << -0.5, -0.1875, 0.4375, -0.25;
    //     gradExp << -0.205283, 0.687338, -0.0722404, -0.117474;
    //
    //     Eigen::JacobiSVD<bwd::Matrix4d, Eigen::FullPivHouseholderQRPreconditioner>
    //         solver(A, Eigen::ComputeFullU | Eigen::ComputeFullV);
    //     resultAct = solver.solve(b);
    //
    //     std::cout << "SVD END" << std::endl;
    //
    //     A(0, 0).visits();
    //     if(A(0, 0).hasCycle({}))
    //         std::cout << "has cycle!" << std::endl;
    //     else
    //         std::cout << "no cycle!" << std::endl;
    //
    //     REQUIRE(Approx(valExp(0)).margin(eps) == resultAct(0).value());
    //     REQUIRE(Approx(valExp(1)).margin(eps) == resultAct(1).value());
    //     REQUIRE(Approx(valExp(2)).margin(eps) == resultAct(2).value());
    //     REQUIRE(Approx(valExp(3)).margin(eps) == resultAct(3).value());
    //
    //     resultAct(0).setGradient(1);
    //     REQUIRE(Approx(gradExp(0)).margin(eps) == A(0, 0).gradient());
    //
    //     resultAct(0).unsetGradient();
    //     resultAct(1).setGradient(1);
    //     REQUIRE(Approx(gradExp(1)).margin(eps) == A(0, 0).gradient());
    //
    //     resultAct(1).unsetGradient();
    //     resultAct(2).setGradient(1);
    //     REQUIRE(Approx(gradExp(2)).margin(eps) == A(0, 0).gradient());
    //
    //     resultAct(2).unsetGradient();
    //     resultAct(3).setGradient(1);
    //     REQUIRE(Approx(gradExp(3)).margin(eps) == A(0, 0).gradient());
    // }

    // SECTION("eigen value decomposition")
    // {
    //     bwd::Matrix4d A;
    //     A << bwd::Double(2, 1), 3, 11, 5,
    //         1, 1, 5, 2,
    //         2, 1, -3, 2,
    //         1, 1, -3, 4;
    //     bwd::Vector4d b;
    //     b << 2, 1, -3, -3;
    //
    //     Eigen::Vector4d eigvalsExp;
    //     eigvalsExp << 7.27048, -5.64984, -0.291657, 2.67103;
    //     Eigen::Vector4d eiggradExp;
    //     eiggradExp <<  0.536189,  0.463811, 0, 0;
    //
    //     Eigen::EigenSolver<bwd::Matrix4d> solver(A);
    //     bwd::Vector4d eigvals = solver.eigenvalues().real();
    //     bwd::Matrix4d eigvecs = solver.eigenvectors().real();
    //
    //     REQUIRE(Approx(eigvalsExp(0)).margin(eps) == eigvals(0).value());
    //     REQUIRE(Approx(eigvalsExp(1)).margin(eps) == eigvals(1).value());
    //     REQUIRE(Approx(eigvalsExp(2)).margin(eps) == eigvals(2).value());
    //     REQUIRE(Approx(eigvalsExp(3)).margin(eps) == eigvals(3).value());
    //
    //     REQUIRE(Approx(eiggradExp(0)).margin(eps) == eigvals(0).gradient());
    //     REQUIRE(Approx(eiggradExp(1)).margin(eps) == eigvals(1).gradient());
    //     REQUIRE(Approx(eiggradExp(2)).margin(eps) == eigvals(2).gradient());
    //     REQUIRE(Approx(eiggradExp(3)).margin(eps) == eigvals(3).gradient());
    // }

    SECTION("multiple outputs")
    {
        bwd::Vector2d x;
        x << bwd::Double(3), bwd::Double(2);

        bwd::Matrix2d c;
        c << bwd::Double(2.1), bwd::Double(3.4),
            bwd::Double(1.6), bwd::Double(2.3);

        Eigen::Vector2d valExp;
        valExp <<
            x(0).value() * c(0, 0).value() +  x(1).value() * c(0, 1).value(),
            x(0).value() * c(1, 0).value() +  x(1).value() * c(1, 1).value();
        Eigen::Matrix2d jacExp;
        jacExp << c(0, 0).value(), c(0, 1).value(),
            c(1, 0).value(), c(1, 1).value();

        bwd::Vector2d f = c * x;
        Eigen::Matrix2d jacAct;
        jacobian(x, f, jacAct);

        REQUIRE_MATRIX_APPROX(valExp, f.template cast<double>(), eps);
        REQUIRE_MATRIX_APPROX(jacExp, jacAct, eps);
    }
}
