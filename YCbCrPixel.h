//
// Created by christopher on 15.11.16.
//

#ifndef DM_MMT_YCBCRPIXEL_H
#define DM_MMT_YCBCRPIXEL_H

using namespace std;

#include <vector>

class YCbCrPixel {
public:
    YCbCrPixel(int y, int cb, int cr);
    YCbCrPixel();

    int getY() const;

    int getCb() const;

    int getCr() const;

private:
    int Y;
    int Cb;
    int Cr;
};

#endif //DM_MMT_YCBCRPIXEL_H
