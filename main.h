//
// Created by christopher on 05.11.16.
//

#ifndef DM_MMT_MAIN_H
#define DM_MMT_MAIN_H

using namespace std;

struct RGBPixel;
struct YCbCrPixel;
struct Subsample;

vector<vector<Subsample>> subsample420(vector<vector<YCbCrPixel>> input);

#endif //DM_MMT_MAIN_H
