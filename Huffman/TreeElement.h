//
// Created by christopher on 05.12.16.
//

#ifndef DM_MMT_TREEELEMENT_H
#define DM_MMT_TREEELEMENT_H

#include <memory>

using namespace std;

class TreeElement {
public:
    TreeElement();

private:
    char value;

    bool valueSet = false;

    TreeElement *left;
    bool leftSet = false;

    TreeElement *right;

    bool rightSet = false;
public:
    bool isRightSet() const;

    TreeElement *getRight() const;

    void setRight(TreeElement *right);

    bool isLeftSet() const;

    bool isValueSet() const;

    char getValue() const;

    void setValue(char value);

    TreeElement *getLeft() const;

    void setLeft(TreeElement *left);
};


#endif //DM_MMT_TREEELEMENT_H
