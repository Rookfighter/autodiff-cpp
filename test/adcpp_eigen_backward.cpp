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
    //     bwd::Matrix4d A;
    //     A << 2, 3, 11, 5,
    //         1, 1, 5, 2,
    //         2, 1, -3, 2,
    //         1, 1, -3, 4;
    //     bwd::Vector4d b;
    //     b << 2, 1, -3, -3;
    //
    //     Eigen::Vector4d valExp;
    //     Eigen::Vector4d gradExp;
    //     valExp << -0.5, -0.1875, 0.4375, -0.25;
    //     gradExp << -0.205283, 0.687338, -0.0722404, -0.117474;
    //
    //     Eigen::JacobiSVD<bwd::Matrix4d, Eigen::FullPivHouseholderQRPreconditioner>
    //         solver(A, Eigen::ComputeFullU | Eigen::ComputeFullV);
    //     bwd::Vector4d f = solver.solve(b);
    //
    //     Eigen::MatrixXd jacAct(4, 4);
    //     std::cout << "jacobian" << std::endl;
    //     jacobian(b, f, jacAct);
    //
    //     std::cout << jacAct << std::endl;
    //     REQUIRE_MATRIX_APPROX(valExp, f.template cast<double>(), eps);
    // }

    // SECTION("eigen value decomposition")
    // {
    //     bwd::Matrix4d A;
    //     A << 2, 3, 11, 5,
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
    //     Eigen::MatrixXd jacAct(4, 4);
    //     std::cout << "jacobian" << std::endl;
    //     jacobian(b, eigvals, jacAct);
    //
    //     REQUIRE_MATRIX_APPROX(eigvalsExp, eigvals.template cast<double>(), eps);
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
