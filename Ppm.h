//
// Created by christopher on 15.11.16.
//

#ifndef DM_MMT_PPM_H
#define DM_MMT_PPM_H

#include "RGBPixel.h"
#include "YCbCrPixel.h"

using namespace std;

class Ppm {
public:
    Ppm();

    void readFile(string filename);

    const vector<vector<RGBPixel>> &getRgbImage() const;

    vector<vector<YCbCrPixel>> getYCbCrImage();

private:
    vector<vector<RGBPixel>> image;
};

#endif //DM_MMT_PPM_H
