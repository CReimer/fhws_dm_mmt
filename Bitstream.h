//
// Created by christopher on 15.11.16.
//

#ifndef DM_MMT_BITSTREAM_H
#define DM_MMT_BITSTREAM_H

#include <vector>
#include <string>
#include <array>

using namespace std;

class Bitstream {
public:
    Bitstream();

    void readFile(string filename);

    void writeFile(string filename);

    void appendBit(bool);

    void prependBit(bool);

    void appendByte(char);

    void finalizeBits();

private:
    vector<char> bytes;
    vector<bool> bits;
public:
    const vector<bool, allocator<bool>> &getBits() const;

private:

    char bit2byte(array<bool, 8>);

};


#endif //DM_MMT_BITSTREAM_H
