//
// Created by christopher on 15.11.16.
//

#ifndef DM_MMT_BITSTREAM_H
#define DM_MMT_BITSTREAM_H

#include <vector>
#include <string>

using namespace std;

class Bitstream {
public:
    Bitstream();

    void readFile(string filename);

    void writeFile(string filename);

    void appendBitAtBeginning(bool);

    void appendBitAtEnd(bool);

    void appendByteAtEnd(char);

private:
    vector<bool> bitstream;

    vector<bool> byte2bit(char byte);
    void bit2byte(vector<bool>);

};


#endif //DM_MMT_BITSTREAM_H
