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
    Tree();

    Bitstream encodeHuffman();

    void generateDictionary();
    void generateDictionary(int maxDepth);

    string decodeHuffman();

    void setHuffman(const Bitstream &huffman);

    void setInputString(const string &inputString);
};


#endif //DM_MMT_TREE_H
