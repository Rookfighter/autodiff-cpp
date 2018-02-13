/*
 * fad.cpp
 *
 *  Created on: 13 Feb 2018
 *      Author: Fabian Meyer
 */

#include <iostream>
#include "ForwardAD.hpp"

int main()
{
    fad::Double x1(3,0);
    fad::Double x2(5,1);

    fad::Double ret = fad::pow(x1 * x2, 2);

    std::cout << "F: " << ret.val() << " J: " << ret.jac() << std::endl;
}
