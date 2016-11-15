//
// Created by christopher on 15.11.16.
//

#include "RGBPixel.h"

RGBPixel::RGBPixel(int r = 0, int g = 0, int b = 0) {
    R = r;
    G = g;
    B = b;
}

int RGBPixel::getR() const {
    return R;
}

int RGBPixel::getG() const {
    return G;
}

int RGBPixel::getB() const {
    return B;
}

RGBPixel::RGBPixel() {
    R = 0;
    G = 0;
    B = 0;
}
