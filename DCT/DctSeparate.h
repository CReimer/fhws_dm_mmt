//
// Created by christopher on 20.12.16.
//

#ifndef DM_MMT_DCTSEPARATE_H
#define DM_MMT_DCTSEPARATE_H


#include "../deps/Eigen/Dense"

class DctSeparate {
public:
    DctSeparate();

    Eigen::MatrixXd Transform(Eigen::MatrixXd input);

    Eigen::MatrixXd Reverse(Eigen::MatrixXd input);

private:
    Eigen::MatrixXd U;

};


#endif //DM_MMT_DCTSEPARATE_H
