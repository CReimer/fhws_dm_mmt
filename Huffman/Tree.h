//
// Created by christopher on 05.12.16.
//

#ifndef DM_MMT_TREE_H
#define DM_MMT_TREE_H

#include <string>
#include "TreeElement.h"

using namespace std;

class Tree {
private:

    string inputString;

    string sortInputElements(string);

    void generateDictionary(string);

    TreeElement *basis;

    void encodeHuffman(string);

public:
    void generateHuffman(string);
};


#endif //DM_MMT_TREE_H
