//
// Created by christopher on 05.12.16.
//

#ifndef DM_MMT_TREE_H
#define DM_MMT_TREE_H

#include <string>
#include <unordered_map>
#include "../Bitstream.h"
#include "TreeNode.h"

using namespace std;

class Tree {
private:
    void sortPriorityQueue();

    string inputString;

    Bitstream huffman;

    vector<TreeNode *> priorityQueue;

    unordered_map<char, string> encodingMap;
    unordered_map<int, vector<char>> countedCharMap;

    void encodingMapWorker(TreeNode *, string bits);

public:
    void setInputString(string input);

    Bitstream encodeHuffman();

    string decodeHuffman();

    void generateHuffmanTree();

    void generateHuffmanEncodingMap();

    const unordered_map<char, string> &getEncodingMap() const;

    unordered_map<int, vector<char>> getCountedCharMap();
};


#endif //DM_MMT_TREE_H
