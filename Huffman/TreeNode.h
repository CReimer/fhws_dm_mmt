//
// Created by christopher on 09.12.16.
//

#ifndef DM_MMT_TREENODE_H
#define DM_MMT_TREENODE_H


class TreeNode {
private:
    char character;
    unsigned long frequency;

    TreeNode *left;
    bool leftSet;
    TreeNode *right;
    bool rightSet;

public:
    TreeNode(char character);

    TreeNode();

    void setCharacter(char character);

    void setFrequency(unsigned long frequency);

    char getCharacter() const;

    void increaseFrequency();

    unsigned long getFrequency() const;

    void setLeft(TreeNode *left);

    void setRight(TreeNode *right);

    TreeNode *getLeft() const;

    TreeNode *getRight() const;

    bool isLeftSet() const;

    bool isRightSet() const;


};


#endif //DM_MMT_TREENODE_H

