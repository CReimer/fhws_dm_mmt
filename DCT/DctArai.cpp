//
// Created by christopher on 20.12.16.
//

#include <iostream>
#include "DctArai.h"

#define M_SQRT1_2 0.707106781186547524401
#define M_PI 3.14159265358979323846

Eigen::MatrixXd DctArai::Transform(Eigen::MatrixXd input) {
    //Based on: http://www.thoughtstuff.com/rme/test-dct.c

    Eigen::MatrixXd stage1 = input;



    int n = (int) input.rows();

    double tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    double tmp10, tmp11, tmp12, tmp13;
    double z1, z2, z3, z4, z5, z11, z13;


    // Durchgang 1: Reihen

    for (int x = 0; x < n; x++) {
        tmp0 = input(x, 0) + input(x, 7);
        tmp7 = input(x, 0) - input(x, 7);
        tmp1 = input(x, 1) + input(x, 6);
        tmp6 = input(x, 1) - input(x, 6);
        tmp2 = input(x, 2) + input(x, 5);
        tmp5 = input(x, 2) - input(x, 5);
        tmp3 = input(x, 3) + input(x, 4);
        tmp4 = input(x, 3) - input(x, 4);


        // Gerader Teil

        tmp10 = tmp0 + tmp3;    /* phase 2 */
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        input(x, 0) = tmp10 + tmp11; /* phase 3 */
        input(x, 4) = tmp10 - tmp11;



        z1 = (tmp12 + tmp13) * M_SQRT1_2; /* c4 */
        input(x, 2) = tmp13 + z1;    /* phase 5 */
        input(x, 6) = tmp13 - z1;

        // Ungerader Teil

        tmp10 = tmp4 + tmp5;    /* phase 2 */
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;

        /* The rotator is modified from fig 4-8 to avoid extra negations. */
        z5 = (tmp10 - tmp12) * 0.382683433; /* c6 */
        z2 = 0.541196100 * tmp10 + z5; /* c2-c6 */
        z4 = 1.306562965 * tmp12 + z5; /* c2+c6 */
        z3 = tmp11 * M_SQRT1_2; /* c4 */

        z11 = tmp7 + z3;        /* phase 5 */
        z13 = tmp7 - z3;

        input(x, 5) = z13 + z2;    /* phase 6 */
        input(x, 3) = z13 - z2;
        input(x, 1) = z11 + z4;
        input(x, 7) = z11 - z4;
    }

    for (int y = 0; y < n; y++) {
        tmp0 = input(0, y) + input(7, y);
        tmp7 = input(0, y) - input(7, y);
        tmp1 = input(1, y) + input(6, y);
        tmp6 = input(1, y) - input(6, y);
        tmp2 = input(2, y) + input(5, y);
        tmp5 = input(2, y) - input(5, y);
        tmp3 = input(3, y) + input(4, y);
        tmp4 = input(3, y) - input(4, y);


        /* Gerader Teil */

        tmp10 = tmp0 + tmp3;    /* phase 2 */
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        input(0, y) = tmp10 + tmp11; /* phase 3 */
        input(4, y) = tmp10 - tmp11;

        z1 = (tmp12 + tmp13) * M_SQRT1_2; /* c4 */
        input(2, y) = tmp13 + z1; /* phase 5 */
        input(6, y) = tmp13 - z1;

        /* Odd part */

        tmp10 = tmp4 + tmp5;    /* phase 2 */
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;

        /* The rotator is modified from fig 4-8 to avoid extra negations. */
        z5 = (tmp10 - tmp12) * 0.382683433; /* c6 */
        z2 = 0.541196100 * tmp10 + z5; /* c2-c6 */
        z4 = 1.306562965 * tmp12 + z5; /* c2+c6 */
        z3 = tmp11 * M_SQRT1_2; /* c4 */

        z11 = tmp7 + z3;        /* phase 5 */
        z13 = tmp7 - z3;

        input(5, y) = z13 + z2; /* phase 6 */
        input(3, y) = z13 - z2;
        input(1, y) = z11 + z4;
        input(7, y) = z11 - z4;
    }

    return input/8;
}
