//
// Created by christopher on 15.11.16.
//

#include <fstream>
#include <vector>
#include <iostream>
#include "Bitstream.h"

using namespace std;

Bitstream::Bitstream() {}

void Bitstream::readFile(string filename) {
    std::ifstream ifs(filename);
    char b;
    vector<bool> bitstream;
    while (ifs.read(&b, 1)) {
        vector<bool> bytevec = byte2bit(b);
        bitstream.insert(bitstream.end(), bytevec.begin(), bytevec.end());
    }
    Bitstream::bitstream = bitstream;
}

void Bitstream::appendBitAtEnd(bool bit) {
    Bitstream::bitstream.push_back(bit);
}

void Bitstream::appendBitAtBeginning(bool bit) {
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

vector<bool> Bitstream::byte2bit(char byte) {
    vector<bool> bitstream;

    for (int i = 0; i < 8; ++i)
        bitstream.push_back((byte & (1 << i)) != 0);

    return bitstream;
}

void Bitstream::bit2byte(vector<bool>) {

}

void Bitstream::appendByteAtEnd(char byte) {
    vector<bool> bits = Bitstream::byte2bit(byte);

//    for (std::vector<bool>::const_iterator i = bits.begin(); i != bits.end(); ++i)
//        std::cout << *i << ' ';
//    std::cout << "\n";
    Bitstream::bitstream.insert(Bitstream::bitstream.end(), bits.begin(), bits.end());

//    for (std::vector<bool>::const_iterator i = Bitstream::bitstream.begin(); i != Bitstream::bitstream.end(); ++i)
//        std::cout << *i << ' ';
//    std::cout << "\n";
}
