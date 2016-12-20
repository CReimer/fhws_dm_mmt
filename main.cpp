#include <iostream>
#include <vector>

#include "main.h"
#include "RGBPixel.h"
#include "YCbCrPixel.h"
#include "Ppm.h"
#include "Bitstream.h"
#include "Jpeg.h"
#include "Huffman/Tree.h"
#include "DCT/DiscreteCosineTransformation.h"
#include "DCT/DctSeparate.h"
#include "DCT/DctDirect.h"
#include "DCT/DctArai.h"

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
//    Tree test;
//    test.setInputString("11111222222222222222222223334444455666666666666666");
//    test.setInputString(
//            "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.");
//    test.generateHuffmanTree();
//    test.generateHuffmanEncodingMap();
//    test.lengthLimitedTree(3);
//    test.getSecondary()->generateHuffmanTree();
//    test.encodeHuffman();
//    cout << test.decodeHuffman() << std::endl;

//    std::cout << "Hello, World!" << std::endl;
//    Ppm PpmImageObj;
//    PpmImageObj.readFile("test.ppm");

//    vector<vector<RGBPixel>> picture = PpmImageObj.getRgbImage();
//    vector<vector<YCbCrPixel>> ypicture = PpmImageObj.getYCbCrImage();
//    vector<vector<Subsample>> subsample = subsample420(ypicture);

//    Bitstream emptyStream;
//    Jpeg jpegGenerator(&emptyStream);
//    jpegGenerator.setSoi();
//    jpegGenerator.setApp0();
//    jpegGenerator.setSof0(PpmImageObj.getX(), PpmImageObj.getY(), 4, 2, 2);
//    jpegGenerator.setDht(test);
//    jpegGenerator.setEoi();
//    emptyStream.writeFile(("./test2.jpg"));

//    test.readFile("./test.ppm");
//    test.writeFile("./test2.ppm");

    Eigen::MatrixXd testBlockA(8, 8);
    testBlockA <<
               100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100,
            100, 100, 100, 100, 100, 100, 100, 100;
    Eigen::MatrixXd testBlockB(8, 8);
    testBlockB <<
               47, 18, 13, 16, 41, 90, 47, 27,
            62, 42, 35, 39, 66, 90, 41, 26,
            71, 55, 56, 67, 55, 40, 22, 39,
            53, 60, 63, 50, 48, 25, 37, 87,
            31, 27, 33, 27, 37, 50, 81, 147,
            54, 31, 33, 46, 58, 104, 144, 179,
            76, 70, 71, 91, 118, 151, 176, 184,
            102, 105, 115, 124, 135, 168, 173, 181;

    DctSeparate *dctsep = new DctSeparate();
    DctDirect *dctdir = new DctDirect();
    DctArai *dctarai = new DctArai();

    Eigen::MatrixXd dct = dctarai->Transform(testBlockB);
    Eigen::MatrixXd idct = dctsep->Reverse(dct);
    cout << dct << std::endl << std::endl;
}
