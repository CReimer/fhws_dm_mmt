//
// Created by christopher on 20.12.16.
//

#include <iostream>
#include "DctSeparate.h"

#define M_PI 3.14159265358979323846
#define M_PI16 (double)M_PI/16
#define M_SQRT1_2 0.707106781186547524401

using namespace std;

DctSeparate::DctSeparate() {
    DctSeparate::U = Eigen::MatrixXd(8, 8);
    DctSeparate::U << M_SQRT1_2, M_SQRT1_2, M_SQRT1_2, M_SQRT1_2, M_SQRT1_2, M_SQRT1_2, M_SQRT1_2, M_SQRT1_2,
            cos(M_PI16), cos(3 * M_PI16), cos(5 * M_PI16), cos(7 * M_PI16), cos(9 * M_PI16), cos(11 * M_PI16), cos(
            13 * M_PI16), cos(15 * M_PI16), cos(2 * M_PI16), cos(6 * M_PI16), cos(10 * M_PI16), cos(14 * M_PI16), cos(
            18 * M_PI16), cos(22 * M_PI16), cos(26 * M_PI16), cos(30 * M_PI16), cos(3 * M_PI16), cos(9 * M_PI16), cos(
            15 * M_PI16), cos(21 * M_PI16), cos(27 * M_PI16), cos(33 * M_PI16), cos(39 * M_PI16), cos(45 * M_PI16), cos(
            4 * M_PI16), cos(12 * M_PI16), cos(20 * M_PI16), cos(28 * M_PI16), cos(36 * M_PI16), cos(44 * M_PI16), cos(
            52 * M_PI16), cos(60 * M_PI16), cos(5 * M_PI16), cos(15 * M_PI16), cos(25 * M_PI16), cos(35 * M_PI16), cos(
            45 * M_PI16), cos(55 * M_PI16), cos(65 * M_PI16), cos(75 * M_PI16), cos(6 * M_PI16), cos(18 * M_PI16), cos(
            30 * M_PI16), cos(42 * M_PI16), cos(54 * M_PI16), cos(66 * M_PI16), cos(78 * M_PI16), cos(90 * M_PI16), cos(
            7 * M_PI16), cos(21 * M_PI16), cos(35 * M_PI16), cos(49 * M_PI16), cos(63 * M_PI16), cos(77 * M_PI16), cos(
            91 * M_PI16), cos(105 * M_PI16);
    DctSeparate::U = DctSeparate::U * 0.5;

}

Eigen::MatrixXd DctSeparate::Transform(Eigen::MatrixXd input) {
    return DctSeparate::U * input * DctSeparate::U.transpose();
}

Eigen::MatrixXd DctSeparate::Reverse(Eigen::MatrixXd input) {
    return DctSeparate::U.transpose() * input * DctSeparate::U;
}

