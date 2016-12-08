//
// Created by christopher on 05.12.16.
//

#include "TreeElement.h"

bool TreeElement::isValueSet() const {
    return valueSet;
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

char TreeElement::getValue() const {
    return value;
}

void TreeElement::setValue(char value) {
    TreeElement::value = value;
    TreeElement::valueSet = true;
}

void TreeElement::setLeft(TreeElement *left) {
    TreeElement::left = left;
    TreeElement::leftSet = true;
}

TreeElement *TreeElement::getLeft() const {
    return left;
}

TreeElement::TreeElement() {
    TreeElement::leftSet = false;
    TreeElement::valueSet = false;
    TreeElement::rightSet = false;
}

