//
// Created by christopher on 05.12.16.
//

#ifndef DM_MMT_TREEELEMENT_H
#define DM_MMT_TREEELEMENT_H

#include <memory>

using namespace std;

class TreeElement {
private:
    TreeElement *base;
    char left;
    bool leftSet = false;
    TreeElement *right;
    bool rightSet = false;
public:
    bool isRightSet() const;

    char getLeft() const;

    void setLeft(const char &left);

    TreeElement *getRight() const;

    void setRight(TreeElement *right);

    void setBase(TreeElement *base);

    bool isLeftSet() const;
};


#endif //DM_MMT_TREEELEMENT_H
