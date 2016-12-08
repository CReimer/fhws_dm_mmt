#include <iostream>
#include <vector>

#include "main.h"
#include "RGBPixel.h"
#include "YCbCrPixel.h"
#include "Ppm.h"
#include "Bitstream.h"
#include "Jpeg.h"
#include "Huffman/Tree.h"

using namespace std;

struct Subsample {
    int Y1;
    int Y2;
    int Y3;
    int Y4;
    int Cb;
    int Cr;

    Subsample(int y1 = 0, int y2 = 0, int y3 = 0, int y4 = 0, int cb = 0, int cr = 0) : Y1(y1), Y2(y2), Y3(y3), Y4(y4),
                                                                                        Cb(cb), Cr(cr) {};

};

vector<vector<Subsample>> subsample420(vector<vector<YCbCrPixel>> input) {
    vector<vector<Subsample>> output(input.size() / 2, vector<Subsample>(input[0].size() / 2));


    for (int y = 0; y < input[0].size(); y++) {
        for (int x = 0; x < input.size(); x++) {
            int y1 = input[x][y].getY();
            int cb1 = input[x][y].getCb();
            int cr1 = input[x][y].getCr();
            x += 1; // 1 nach rechts

            int y2 = input[x][y].getY();
            int cb2 = input[x][y].getCb();
            int cr2 = input[x][y].getCr();
            x -= 1; // 1 nach links
            y += 1; // neue Zeile

            int y3 = input[x][y].getY();
            int cb3 = input[x][y].getCb();
            int cr3 = input[x][y].getCr();
            x += 1; // 1 nach rechts

            int y4 = input[x][y].getY();
            int cb4 = input[x][y].getCb();
            int cr4 = input[x][y].getCr();
            y -= 1; //

            int cb = (cb1 + cb2 + cb3 + cb4) / 4;
            int cr = (cr1 + cr2 + cr3 + cr4) / 4;

            int xo = (x - 1) / 2;
            int yo = y / 2;
            output[xo][yo] = Subsample(y1, y2, y3, y4, cb, cr);
        }
        y += 1; // Zwei Zeilen abgearbeitet. Springe zur nächsten
    }
    return output;
}

int main() {
    Tree test;

    Bitstream ddd = test.generateHuffman("Dies ist ein Teststring");
    test.decodeHuffman(ddd);




//    std::cout << "Hello, World!" << std::endl;
//    Ppm PpmImageObj;
//    PpmImageObj.readFile("test.ppm");

//    vector<vector<RGBPixel>> picture = PpmImageObj.getRgbImage();
//    vector<vector<YCbCrPixel>> ypicture = PpmImageObj.getYCbCrImage();
//    subsample420(ypicture);

//    Bitstream emptyStream;
//    Jpeg jpegGenerator(&emptyStream);
//    jpegGenerator.setSoi();
//    jpegGenerator.setApp0();
//    jpegGenerator.setSof0(PpmImageObj.getX(), PpmImageObj.getY(),4,2,2);
//    jpegGenerator.setEoi();
//    emptyStream.writeFile(("./test2.jpg"));

//    Bitstream test;
//    test.appendBit(1);
//    test.appendBit(0);
//    test.appendBit(1);
//    test.appendBit(0);
//    test.appendBit(1);
//    test.appendBit(0);
//    test.appendBit(1);
//    test.appendBit(0);
//
//    test.appendBit(1);
//    test.appendBit(0);
//    test.appendBit(1);
//    test.appendBit(0);
//    test.appendBit(1);
//    test.appendBit(0);
//    test.finalizeBits();
//    test.readFile("./test.ppm");
//    test.writeFile("./test2.ppm");

    return 0;
}
