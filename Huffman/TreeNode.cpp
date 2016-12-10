//
// Created by christopher on 09.12.16.
//

#include "TreeNode.h"

void TreeNode::setCharacter(char character) {
    TreeNode::character = character;
}

void TreeNode::setFrequency(char frequency) {
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
    TreeNode::leftSet = false;
    TreeNode::rightSet = false;
}

char TreeNode::getFrequency() const {
    return frequency;
}

TreeNode::TreeNode() {
//    TreeNode::frequency = 1;
//    TreeNode::leftSet = false;
//    TreeNode::rightSet = false;
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

