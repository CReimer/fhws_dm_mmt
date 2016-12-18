//
// Created by christopher on 18.12.16.
//

#include <array>
#include <vector>
#include <complex>
#include "DiscreteCosineTransformation.h"

#define PI 3.14159265

vector<vector<float>> DiscreteCosineTransformation::idct(vector<vector<float>> input) {
    int sizeX = (int) input.size();
    int sizeY = (int) input[0].size();

    vector<vector<float>> output = input;

    int i, j, u, v;
    for (u = 0; u < sizeX; ++u) {
        for (v = 0; v < sizeY; ++v) {
            output[u][v] = (float) (1 / 4. * input[0][0]);
            for (i = 1; i < sizeX; i++) {
                output[u][v] += 1 / 2. * input[i][0];
            }
            for (j = 1; j < sizeY; j++) {
                output[u][v] += 1 / 2. * input[0][j];
            }

            for (i = 1; i < sizeX; i++) {
                for (j = 1; j < sizeY; j++) {
                    output[u][v] += input[i][j] * cos(PI / ((float) sizeX) * (u + 1. / 2.) * i) *
                                    cos(PI / ((float) sizeY) * (v + 1. / 2.) * j);
                }
            }
            output[u][v] *= 2. / ((float) sizeX) * 2. / ((float) sizeY);
        }
    }

    return output;
}

vector<vector<float>> DiscreteCosineTransformation::dctDirect(vector<vector<float>> input) {
    int n = (int) input.size();
    double ca;
    double cb;
    double tmpXab = 0.0;
    double cmpnt;

    vector<vector<float>> output = input;

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    cmpnt = input[x][y] * cos(((2.0 * x + 1.0) * a * PI) / (2.0 * n)) *
                            cos((2.0 * y + 1.0) * b * PI / (2 * n));
                    tmpXab += cmpnt;
                    cmpnt = 0.0;
                }
            }
            if (a == 0)
                ca = (1.0 / sqrt(2.0));
            else
                ca = 1.0;

            if (b == 0)
                cb = (1.0 / sqrt(2.0));
            else
                cb = 1.0;

            output[a][b] = (float) ((2.0 / n) * ca * cb * tmpXab);
            tmpXab = 0.0;
        }
    }

    return output;
}

vector<vector<float>> DiscreteCosineTransformation::dctSeparated(vector<vector<float>> input) {

    vector<vector<float>> output = input;

    int sizeX = (int) input.size();
    int sizeY = (int) input[0].size();


    int i, j, u, v;
    for (u = 0; u < sizeX; u++) {
        for (v = 0; v < sizeY; v++) {
            output[u][v] = 0;
            for (i = 0; i < sizeX; i++) {
                for (j = 0; j < sizeY; j++) {
                    output[u][v] += input[i][j] * cos(PI / ((float) sizeX) * (i + 1. / 2.) * u) *
                                    cos(PI / ((float) sizeY) * (j + 1. / 2.) * v);
                }
            }
        }
    }
    return output;
}

vector<vector<float>> DiscreteCosineTransformation::dctArai(vector<vector<float>> input) {
    //Based on: http://www.thoughtstuff.com/rme/test-dct.c

    float tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    float tmp10, tmp11, tmp12, tmp13;
    float z1, z2, z3, z4, z5, z11, z13;
    int n = (int) input.size();

    // Durchgang 1: Reihen

    for (int x = 0; x < n; x++) {
        tmp0 = input[x][0] + input[x][7];
        tmp7 = input[x][0] - input[x][7];
        tmp1 = input[x][1] + input[x][6];
        tmp6 = input[x][1] - input[x][6];
        tmp2 = input[x][2] + input[x][5];
        tmp5 = input[x][2] - input[x][5];
        tmp3 = input[x][3] + input[x][4];
        tmp4 = input[x][3] - input[x][4];

        // Gerader Teil

        tmp10 = tmp0 + tmp3;    /* phase 2 */
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        input[x][0] = tmp10 + tmp11; /* phase 3 */
        input[x][4] = tmp10 - tmp11;

        z1 = (float) ((tmp12 + tmp13) * 0.707106781); /* c4 */
        input[x][2] = tmp13 + z1;    /* phase 5 */
        input[x][6] = tmp13 - z1;

        // Ungerader Teil

        tmp10 = tmp4 + tmp5;    /* phase 2 */
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;

        // Rotator
        z5 = (float) ((tmp10 - tmp12) * (0.382683433)); /* c6 */
        z2 = (float) ((0.541196100) * tmp10 + z5); /* c2-c6 */
        z4 = (float) ((1.306562965) * tmp12 + z5); /* c2+c6 */
        z3 = (float) (tmp11 * (0.707106781)); /* c4 */

        z11 = tmp7 + z3;        /* phase 5 */
        z13 = tmp7 - z3;

        input[x][5] = z13 + z2;    /* phase 6 */
        input[x][3] = z13 - z2;
        input[x][1] = z11 + z4;
        input[x][7] = z11 - z4;
    }

    for (int y = 0; y < n; y++) {
        tmp0 = input[0][y] + input[7][y];
        tmp7 = input[0][y] - input[7][y];
        tmp1 = input[1][y] + input[6][y];
        tmp6 = input[1][y] - input[6][y];
        tmp2 = input[2][y] + input[5][y];
        tmp5 = input[2][y] - input[5][y];
        tmp3 = input[3][y] + input[4][y];
        tmp4 = input[3][y] - input[4][y];


        /* Gerader Teil */

        tmp10 = tmp0 + tmp3;	/* phase 2 */
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        input[0][y] = tmp10 + tmp11; /* phase 3 */
        input[4][y] = tmp10 - tmp11;

        z1 = (float) ((tmp12 + tmp13) * (0.707106781)); /* c4 */
        input[2][y] = tmp13 + z1; /* phase 5 */
        input[6][y] = tmp13 - z1;

        /* Odd part */

        tmp10 = tmp4 + tmp5;	/* phase 2 */
        tmp11 = tmp5 + tmp6;
        tmp12 = tmp6 + tmp7;

        /* The rotator is modified from fig 4-8 to avoid extra negations. */
        z5 = (float) ((tmp10 - tmp12) * (0.382683433)); /* c6 */
        z2 = (float) (0.541196100) * tmp10 + z5; /* c2-c6 */
        z4 = (float) (1.306562965) * tmp12 + z5; /* c2+c6 */
        z3 = (float) (tmp11 * (0.707106781)); /* c4 */

        z11 = tmp7 + z3;		/* phase 5 */
        z13 = tmp7 - z3;

        input[5][y] = z13 + z2; /* phase 6 */
        input[3][y] = z13 - z2;
        input[1][y] = z11 + z4;
        input[7][y] = z11 - z4;
    }

    return vector<vector<float>>();
}
