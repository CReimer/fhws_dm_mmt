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

vector<vector<float>> DiscreteCosineTransformation::dct(vector<vector<float>> input) {
    int sizeX = (int) input.size();
    int sizeY = (int) input[0].size();

    vector<vector<float>> output = input;

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
