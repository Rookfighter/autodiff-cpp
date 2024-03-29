/* eigen_require.hpp
 *
 *  Created on: 27 Jun 2019
 *      Author: Fabian Meyer
 */

#ifndef ADCPP_EIGEN_REQUIRE_HPP_
#define ADCPP_EIGEN_REQUIRE_HPP_

#include <Eigen/Geometry>
#include <catch2/catch.hpp>

#define REQUIRE_MATRIX_APPROX(a, b, eps) do {                                 \
        REQUIRE(a.cols() == b.cols());                                        \
        REQUIRE(a.rows() == b.rows());                                        \
        for(long int _c = 0; _c < a.cols(); ++_c)                                \
            for(long int _r = 0; _r < a.rows(); ++_r)                            \
                REQUIRE(Approx(a(_r, _c)).margin(eps) == b(_r, _c));          \
    } while(0)

#define REQUIRE_MATRIX(a, b) do {                                             \
        REQUIRE(a.cols() == b.cols());                                        \
        REQUIRE(a.rows() == b.rows());                                        \
        for(long int _c = 0; _c < a.cols(); ++_c)                                \
            for(long int _r = 0; _r < a.rows(); ++_r)                            \
                REQUIRE(a(_r, _c) == b(_r, _c));                              \
    } while(0)

#endif
