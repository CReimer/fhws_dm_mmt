//
// Created by christopher on 05.12.16.
//

#include "TreeElement.h"

void TreeElement::setBase(TreeElement *base) {
    TreeElement::base = base;
}

void TreeElement::setLeft(const char &left) {
    TreeElement::left = left;
    TreeElement::leftSet = true;
}

char TreeElement::getLeft() const {
    return left;
}

bool TreeElement::isLeftSet() const {
    return leftSet;
}

void TreeElement::setRight(TreeElement *right) {
    TreeElement::right = right;
    TreeElement::rightSet = true;
}

TreeElement *TreeElement::getRight() const {
    return right;
}

bool TreeElement::isRightSet() const {
    return rightSet;
}

