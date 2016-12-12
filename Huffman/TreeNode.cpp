//
// Created by christopher on 09.12.16.
//

#include <cstring>
#include "TreeNode.h"

void TreeNode::setCharacter(char character) {
    TreeNode::character = character;
}

void TreeNode::setFrequency(unsigned long frequency) {
    TreeNode::frequency = frequency;
}

char TreeNode::getCharacter() const {
    return character;
}

void TreeNode::increaseFrequency() {
    TreeNode::frequency++;
}

TreeNode::TreeNode(char character) : character(character) {
    TreeNode::frequency = 1;
    TreeNode::left = NULL;
    TreeNode::right = NULL;
    TreeNode::leftSet = false;
    TreeNode::rightSet = false;
}

unsigned long TreeNode::getFrequency() const {
    if (!frequency) {
        return 0;
    }
    return frequency;
}

TreeNode::TreeNode() {
    TreeNode::frequency = NULL;
    TreeNode::left = NULL;
    TreeNode::right = NULL;
    TreeNode::leftSet = false;
    TreeNode::rightSet = false;
}

void TreeNode::setLeft(TreeNode *left) {
    TreeNode::left = left;
    TreeNode::leftSet = true;
}

void TreeNode::setRight(TreeNode *right) {
    TreeNode::right = right;
    TreeNode::rightSet = true;
}

TreeNode *TreeNode::getLeft() const {
    return left;
}

TreeNode *TreeNode::getRight() const {
    return right;
}

bool TreeNode::isLeftSet() const {
    return leftSet;
}

bool TreeNode::isRightSet() const {
    return rightSet;
}

