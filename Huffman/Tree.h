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

    TreeNode* treeBaseNode;

    unordered_map<char, string> encodingMap;
    unordered_map<int, vector<char>> countedCharMap;

    void encodingMapWorker(TreeNode *, string bits);

    void lengthLimitedWorker(TreeNode *, unsigned int level, unsigned int current_level);

    Tree* secondary;

public:
    Tree(bool);

    Tree();

    void setInputString(string input);

    Bitstream encodeHuffman();

    string decodeHuffman();

    void generateHuffmanTree();

    void generateHuffmanEncodingMap();

    const unordered_map<char, string> &getEncodingMap() const;

    unordered_map<int, vector<char>> getCountedCharMap();

    void lengthLimitedTree(unsigned int);

    void addToPriorityQueue(TreeNode*);

    Tree *getSecondary() const;


};


#endif //DM_MMT_TREE_H
