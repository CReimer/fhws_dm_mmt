//
// Created by christopher on 15.11.16.
//

#include "YCbCrPixel.h"

YCbCrPixel::YCbCrPixel(int y, int cb, int cr) {
    Y = y;
    Cb = cb;
    Cr = cr;
}

int YCbCrPixel::getCr() const {
    return Cr;
}

int YCbCrPixel::getCb() const {
    return Cb;
}

int YCbCrPixel::getY() const {
    return Y;
}

YCbCrPixel::YCbCrPixel() {
    Y = 0;
    Cb = 0;
    Cr = 0;
}

