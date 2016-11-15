//
// Created by christopher on 15.11.16.
//

#include <fstream>
#include <vector>
#include "Bitstream.h"

using namespace std;

Bitstream::Bitstream() {}

void Bitstream::readFile(string filename) {
    std::ifstream ifs(filename);
    char b;
    vector<bool> bitstream;
    while (ifs.read(&b, 1)) {
        for (int i = 0; i < 8; ++i)
            bitstream.push_back((b & (1 << i)) != 0);
    }
    Bitstream::bitstream = bitstream;
}

void Bitstream::appendAtEnd(bool bit) {
    Bitstream::bitstream.push_back(bit);
}

void Bitstream::appendAtBeginning(bool bit) {
    Bitstream::bitstream.insert(Bitstream::bitstream.begin(), bit);
}

void Bitstream::writeFile(string filename) {
    std::ofstream ofs(filename);


    int i = 0;
    while (Bitstream::bitstream.size() > i) {
        char c = 0;
        for (int j = 0; j < 8; j++) {
            if (Bitstream::bitstream[i + j]) {
                c |= 1 << j;
            }
        }
        i += 8;
        ofs.write(&c, 1);
    }
}
