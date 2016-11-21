//
// Created by christopher on 15.11.16.
//

#include <fstream>
#include <vector>
#include <iostream>
#include <bitset>
#include "Bitstream.h"

using namespace std;

Bitstream::Bitstream() {}

void Bitstream::readFile(string filename) {
    std::ifstream ifs(filename);
    char b;

    while (ifs.read(&b, 1)) {
        Bitstream::appendByte(b);
    }
}

void Bitstream::appendBit(bool bit) {
    Bitstream::bits.push_back(bit);
}

void Bitstream::prependBit(bool bit) {
    Bitstream::bits.insert(Bitstream::bits.begin(), bit);
}

void Bitstream::writeFile(string filename) {
    std::ofstream ofs(filename);
    for (int i = 0; i < Bitstream::bytes.size(); i++) {
        char byte = Bitstream::bytes[i];
        ofs.write(&byte, 1);
    }
}

char Bitstream::bit2byte(array<bool, 8> bits) {
    bitset<8> bitset;

    for (size_t i = 0; i < 8; i++) {
        bitset.set(i, bits[i]);
    }
    cout << bitset.to_string();
    char byte = static_cast<unsigned char>( bitset.to_ulong() );
    return byte;

}

void Bitstream::appendByte(char byte) {
    Bitstream::bytes.push_back(byte);
}

void Bitstream::finalizeBits() {
    array<bool, 8> bytecache;
    bytecache.fill(0);
    int j = 0;
    for (int i = 0; i < Bitstream::bits.size(); i++) {
        if (j == 8) {
            j = 0;
            Bitstream::bit2byte(bytecache);
            bytecache.fill(0);
        }
        bytecache[j] = Bitstream::bits[i];
        j++;
    }
    Bitstream::appendByte(Bitstream::bit2byte(bytecache));
    Bitstream::bits.empty();
}
