//
// Created by christopher on 05.12.16.
//

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "Tree.h"

string Tree::sortInputElements(string input) {
    unordered_map<char, unsigned int> count;

    string output;

    for (char character : input) {
        if (!count[character]) {
            output += character;
        }
        count[character]++;
    }

    std::sort(std::begin(output), std::end(output),
              [&](const char &lhs, const char &rhs) {
                  return count[lhs] > count[rhs];
              }
    );
    return output;
}

void Tree::generateDictionary() {
    string sorted = sortInputElements(Tree::inputString);
    TreeElement *current = Tree::basis;
    for (char character: sorted) {
        TreeElement *next = new TreeElement;
        current->setLeft(character);
        current->setRight(next);
        current = next;
    }
}

Bitstream Tree::encodeHuffman() {
    Bitstream output;
    for (char character: Tree::inputString) {
        TreeElement *current = Tree::basis;
        while (current->isRightSet()) {
            if (current->getLeft() == character) {
                output.appendBit(1);
                break;
            } else {
                output.appendBit(0);
                current = current->getRight();
            }
        }
    }
    Tree::huffman = output;
    return output;
}

string Tree::decodeHuffman() {
    string output;
    TreeElement *current = Tree::basis;
    for (bool character: Tree::huffman.getBits()) {
        if (character) {
            output += current->getLeft();
            current = Tree::basis;
        } else {
            current = current->getRight();
        }

    }
    return output;
}

void Tree::setInputString(const string &inputString) {
    Tree::inputString = inputString;
}

void Tree::setHuffman(const Bitstream &huffman) {
    Tree::huffman = huffman;
}
