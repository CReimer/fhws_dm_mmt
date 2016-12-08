//
// Created by christopher on 05.12.16.
//

#ifndef DM_MMT_TREE_H
#define DM_MMT_TREE_H

#include <string>
#include "TreeElement.h"
#include "../Bitstream.h"

using namespace std;

class Tree {
private:

    string inputString;

    string sortInputElements(string);

    TreeElement *basis;

    Bitstream huffman;
public:
    void setHuffman(const Bitstream &huffman);
    Bitstream encodeHuffman();
    void generateDictionary();
    string decodeHuffman();
    void setInputString(const string &inputString);
};


#endif //DM_MMT_TREE_H
