//
// Created by christopher on 17.11.16.
//

#ifndef DM_MMT_JPEG_H
#define DM_MMT_JPEG_H


#include "Bitstream.h"

using namespace std;

class Jpeg {
public:
    Jpeg(Bitstream *bitstream);

    void setApp0();

    void setSof0(int, int, int, int, int);

    void setSoi();

    void setEoi();

private:
    Bitstream *bitstream;

    void writeArray(vector<unsigned char>);

};


#endif //DM_MMT_JPEG_H
