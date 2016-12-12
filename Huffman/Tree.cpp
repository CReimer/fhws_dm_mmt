//
// Created by christopher on 05.12.16.
//

#include <algorithm>
#include <iostream>
#include "Tree.h"

Bitstream Tree::encodeHuffman() {
    Bitstream output;

    for (char character: Tree::inputString) {
        for (char bit: Tree::encodingMap[character]) {
            if (bit == '1') {
                output.appendBit(1);
                cout << "1";
            } else {
                output.appendBit(0);
                cout << "0";
            }
        }
    }
//    cout << Tree::encodingMap[(char) '\0'];
//    cout << std::endl;
    Tree::huffman = output;
    return output;
}

string Tree::decodeHuffman() {

    string output;
    TreeNode *current = Tree::priorityQueue[0];
    for (bool character: Tree::huffman.getBits()) {

        if (character) {
            current = current->getRight();
        } else {
            current = current->getLeft();
        }

        if (!current->isLeftSet() && !current->isRightSet()) {
            output += current->getCharacter();
            current = Tree::priorityQueue[0];
        }
    }
    return output;
}

void Tree::sortPriorityQueue() {
    // Bring priorityQueue in the right order
    std::stable_sort(std::begin(Tree::priorityQueue), std::end(Tree::priorityQueue),
              [&](TreeNode *lhs, TreeNode *rhs) {
                  if(lhs && rhs) {
                      if (lhs->getFrequency() >= rhs->getFrequency() || rhs->isLeftSet()) {
                          return true;
                      }
                  }
              }
    );
//    std::sort(std::begin(Tree::priorityQueue), std::end(Tree::priorityQueue),
//              [&](TreeNode *lhs, TreeNode *rhs) {
//                  if(lhs && rhs) {
//                      if (lhs->getFrequency() >= rhs->getFrequency() || rhs->isLeftSet()) {
//                          return true;
//                      }
//                  }
//              }
//    );
    for (TreeNode* current: Tree::priorityQueue) {
        cout << current->getCharacter() << " ";
    }
    cout << std::endl;
}

void Tree::setInputString(string input) {
    Tree::inputString = input;
    // Push characters in queue or increase frequency
    for (char character:input) {
        bool found = false;
        for (TreeNode *current: Tree::priorityQueue) {
            if (current->getCharacter() == character) {
                current->increaseFrequency();
                found = true;
                break;
            }
        }
        if (found) continue;
        TreeNode *newNode = new TreeNode(character);
        Tree::priorityQueue.push_back(newNode);
    }
    // EOF
//    Tree::priorityQueue.push_back(new TreeNode((char) '\0'));
    Tree::sortPriorityQueue();

//    for (TreeNode *current: Tree::priorityQueue) {
//        cout << current->getCharacter() << ":   " << (int) current->getFrequency() << std::endl;
//    }
}

void Tree::generateHuffmanTree() {

    while (Tree::priorityQueue.size() > 1) {
        TreeNode *newNode = new TreeNode();
        newNode->setLeft(Tree::priorityQueue.back());
        Tree::priorityQueue.pop_back();
        newNode->setRight(Tree::priorityQueue.back());
        Tree::priorityQueue.pop_back();

        newNode->setFrequency(newNode->getLeft()->getFrequency() + newNode->getRight()->getFrequency());
        Tree::priorityQueue.push_back(newNode);
        Tree::sortPriorityQueue();
    }

}

void Tree::generateHuffmanEncodingMap() {
    Tree::encodingMapWorker(Tree::priorityQueue[0], "");
}

void Tree::encodingMapWorker(TreeNode *input, string bits) {
    if (input->isLeftSet()) {
        Tree::encodingMapWorker(input->getLeft(), bits + '1');
    }

    if (input->isRightSet()) {
        Tree::encodingMapWorker(input->getRight(), bits + '0');
    }

    if (!input->isRightSet() && !input->isLeftSet()) {
        Tree::encodingMap[input->getCharacter()] = bits;
        cout << bits << ":    "<< std::hex  << (int)input->getCharacter() << std::endl;
    }
}

const unordered_map<char, string> &Tree::getEncodingMap() const {
    return encodingMap;
}

unordered_map<int, vector<char>> Tree::getCountedCharMap() {
    unordered_map<char, bool> seen;
    int maxLength = 0;
    for (char character: Tree::inputString) {
        if (!seen[character]) {
            int length = (int) Tree::encodingMap[character].length();
            if (maxLength < length) {
                maxLength = length;
            }
            Tree::countedCharMap[length].push_back(character);
            seen[character] = true;
        }
    }

//    for (int i; i <= maxLength; i++) {
//        if(!Tree::countedCharMap[i].size()>0) {
//            vector<char> blub;
//            Tree::countedCharMap[i] = blub;
//        }
//    }

    return Tree::countedCharMap;
}
