//
// Created by christopher on 20.12.16.
//

#ifndef DM_MMT_DCTARAI_H
#define DM_MMT_DCTARAI_H


#include "../deps/Eigen/Dense"

class DctArai {
public:
    Eigen::MatrixXd Transform(Eigen::MatrixXd input);
};


#endif //DM_MMT_DCTARAI_H
