//
// Created by christopher on 17.11.16.
//

#include <iostream>
#include <cmath>
#include "Jpeg.h"

void Jpeg::setSof0(int x, int y, int sampleY, int sampleCb, int sampleCr) {
    vector<unsigned char> header = {0xFF, 0xC0};
    vector<unsigned char> length = {0x00, 2 + 1 + 2 + 2 + 1 + 3 + 3 + 3};
    vector<unsigned char> precision = {8};

    vector<unsigned char> height = vector<unsigned char>(2);
    if (y > 255) {
        height[0] = (unsigned char) (y >> 8 & 0xFF);
        height[1] = (unsigned char) (y & 0xFF);
    } else {
        height[0] = 0x00;
        height[1] = (unsigned char) y;
    }

    vector<unsigned char> width = vector<unsigned char>(2);
    if (x > 255) {
        width[0] = (unsigned char) (x >> 8 & 0xFF);
        width[1] = (unsigned char) (x & 0xFF);
    } else {
        width[0] = 0x00;
        width[1] = (unsigned char) x;
    }
    vector<unsigned char> componentCount = {3};
    char by = (char) sqrt(sampleY);
    char ay = by << 4;
    vector<unsigned char> comp1 = {1, ay | by, 0};

    char bcb = (char) sqrt(sampleCb);
    char acb = bcb << 4;
    vector<unsigned char> comp2 = {2, acb | bcb, 0};

    char bcr = (char) sqrt(sampleCr);
    char acr = bcr << 4;
    vector<unsigned char> comp3 = {2, acr | bcr, 1};

    Jpeg::writeArray(header);
    Jpeg::writeArray(length);
    Jpeg::writeArray(precision);
    Jpeg::writeArray(height);
    Jpeg::writeArray(width);
    Jpeg::writeArray(componentCount);
    Jpeg::writeArray(comp1);
    Jpeg::writeArray(comp2);
    Jpeg::writeArray(comp3);
}

void Jpeg::setApp0() {
    vector<unsigned char> header = {0xFF, 0xE0};
    vector<unsigned char> length = {0x00, 16};
    vector<unsigned char> identifier = {0x4A, 0x46, 0x49, 0x46, 0x00}; // ASCII "JFIF" mit 0 terminiert
    vector<unsigned char> version = {0x01, 0x02}; // JFIF Version 1.02
    vector<unsigned char> units = {0x00}; // 00=Keine Einheit, 01=Pixel per Inch, 02=Pixel per Centimeter
    vector<unsigned char> Xdensity = {0x00, 0x01}; //X Density??
    vector<unsigned char> Ydensity = {0x00, 0x01}; //Y Density??
    vector<unsigned char> Xthumb = {0x00}; // Vorschaubild abgeschaltet
    vector<unsigned char> Ythumb = {0x00}; // Vorschaubild abgeschaltet

    Jpeg::writeArray(header);
    Jpeg::writeArray(length);
    Jpeg::writeArray(identifier);
    Jpeg::writeArray(version);
    Jpeg::writeArray(units);
    Jpeg::writeArray(Xdensity);
    Jpeg::writeArray(Ydensity);
    Jpeg::writeArray(Xthumb);
    Jpeg::writeArray(Ythumb);
}

void Jpeg::setSoi() {
    char header[2] = {(char) 0xFF, (char) 0xD8};

    Jpeg::bitstream->appendByte(header[0]);
    Jpeg::bitstream->appendByte(header[1]);

}

Jpeg::Jpeg(Bitstream *bitstream) {
    Jpeg::bitstream = bitstream;
}

void Jpeg::setEoi() {
    char header[2] = {(char) 0xFF, (char) 0xD9};

    Jpeg::bitstream->appendByte(header[0]);
    Jpeg::bitstream->appendByte(header[1]);
}

void Jpeg::writeArray(vector<unsigned char> array) {
    for (int i = 0; i < array.size(); i++) {
//        cout << array[i] << "\n";
        Jpeg::bitstream->appendByte((char) array[i]);
    }
}

void Jpeg::setDht(Tree huffman) {
    char header[2] = {(char) 0xFF, (char) 0xC4};
    Jpeg::bitstream->appendByte(header[0]);
    Jpeg::bitstream->appendByte(header[1]);

    //TODO
    vector<char> temporary;
    int size = 0;
//    char size;

    char type = 0x00; //TODO 00=Y, 01=Cb+Cr
    temporary.push_back(type);
    size++;


    unordered_map<int, vector<char>> input = huffman.getCountedCharMap();
    for (char i = 1; i <= 16; i++) {
//        int test = input[i].size();
        if (input[i].size() > 0) {
            temporary.push_back((char)input[i].size());
        }
        else {
            temporary.push_back(0);
        }
        size++;
    }

    for (int i = 1; i < 16; i++) {
        if (input[i].size() > 0) {
            for (char element: input[i]) {
                size++;
                temporary.push_back(element);
            }

        }
    }

    Jpeg::writeArray({0x00,(char)size});
    size+=2;
//    Jpeg::bitstream->appendByte(size);
    for (char current: temporary) {
        Jpeg::bitstream->appendByte(current);
    }
}
