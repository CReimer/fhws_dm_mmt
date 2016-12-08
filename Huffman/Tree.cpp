//
// Created by christopher on 05.12.16.
//

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "Tree.h"

Tree::Tree() {
    Tree::basis = new TreeElement();
}

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
        current->setValue(character);
        current->setRight(next);
        current = next;
    }
}

Bitstream Tree::encodeHuffman() {
    Bitstream output;
    for (char character: Tree::inputString) {
        TreeElement *current = Tree::basis;
        TreeElement *tempBase = Tree::basis;
        while (current->isValueSet()) {
            if (current->getValue() == character) {
                output.appendBit(1);
                break;
            } else {
                output.appendBit(0);
                if (current->isRightSet()) {
                    current = current->getRight();
                } else {
                    current = tempBase;
                    if (tempBase->isLeftSet())
                        tempBase = tempBase->getLeft();
                }

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
            output += current->getValue();
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

void Tree::generateDictionary(int maxDepth) {
    int currentDepth = 0;
    string sorted = sortInputElements(Tree::inputString);
    TreeElement *current = Tree::basis;
    for (char character: sorted) {
        TreeElement *next = new TreeElement;
        current->setValue(character);

        if (currentDepth >= maxDepth) {
            TreeElement *temp = Tree::basis;
            currentDepth = 0;
            while (temp->isLeftSet()) {
                temp = temp->getLeft();
                currentDepth++;
                if (currentDepth >= maxDepth) {
                    throw "No space left";
                }
            }
            temp->setLeft(next);
            current = temp->getLeft();
//            currentDepth++;

        } else {
            current->setRight(next);
            current = next;
        }
        currentDepth++;
    }
}
