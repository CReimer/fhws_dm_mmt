//
// Created by christopher on 15.11.16.
//

#ifndef DM_MMT_BITSTREAM_H
#define DM_MMT_BITSTREAM_H

using namespace std;

class Bitstream {
public:
    Bitstream();

    void readFile(string filename);

    void writeFile(string filename);

    void appendAtBeginning(bool);

    void appendAtEnd(bool);

private:
    vector<bool> bitstream;

};


#endif //DM_MMT_BITSTREAM_H
