//
// Created by christopher on 15.11.16.
//

#ifndef DM_MMT_RGBPIXEL_H
#define DM_MMT_RGBPIXEL_H


class RGBPixel {
public:
    RGBPixel(int r, int g, int b);
    RGBPixel();

    int getR() const;

    int getG() const;

    int getB() const;

private:
    int R;
    int G;
    int B;
};


#endif //DM_MMT_RGBPIXEL_H
