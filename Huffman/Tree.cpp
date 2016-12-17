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
    TreeNode *current = Tree::treeBaseNode;
    for (bool character: Tree::huffman.getBits()) {

        if (character) {
            current = current->getRight();
        } else {
            current = current->getLeft();
        }

        if (!current->isLeftSet() && !current->isRightSet()) {
            output += current->getCharacter();
            current = Tree::treeBaseNode;
        }
    }
    return output;
}

void Tree::sortPriorityQueue() {
    // Bring priorityQueue in the right order
    std::stable_sort(std::begin(Tree::priorityQueue), std::end(Tree::priorityQueue),
                     [&](TreeNode *lhs, TreeNode *rhs) {
                         if (lhs && rhs) {
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
    for (TreeNode *current: Tree::priorityQueue) {
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
    Tree::treeBaseNode = Tree::priorityQueue[0];

}

void Tree::generateHuffmanEncodingMap() {
    Tree::encodingMapWorker(Tree::treeBaseNode, "");
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
        cout << bits << ":    " << std::hex << (int) input->getCharacter() << std::endl;
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

void Tree::lengthLimitedTree(unsigned int max_level) {
    Tree::lengthLimitedWorker(Tree::treeBaseNode, max_level, 0);
}

void Tree::lengthLimitedWorker(TreeNode *input, unsigned int level, unsigned int current_level) {
    if (current_level == level) {
        if (input->isLeftSet()) {
            Tree::secondary->addToPriorityQueue(input->getLeft());
            input->unsetLeft();
        }

        if (input->isRightSet()) {
            Tree::secondary->addToPriorityQueue(input->getRight());
            input->unsetRight();
        }
    } else {
        if (input->isLeftSet()) {
            Tree::lengthLimitedWorker(input->getLeft(), level, current_level + 1);
        }

        if (input->isRightSet()) {
            Tree::lengthLimitedWorker(input->getRight(), level, current_level + 1);
        }
    }
}

void Tree::addToPriorityQueue(TreeNode *newElement) {
    Tree::priorityQueue.push_back(newElement);
}

Tree::Tree(bool isSecondary) {
    // Don't initialize secondary tree here to avoid segfault
}

Tree::Tree() {
    Tree::secondary = new Tree(true);
}

Tree *Tree::getSecondary() const {
    return secondary;
}

TreeNode *Tree::getTreeBaseNode() const {
    return treeBaseNode;
}

//wie der name vermuten lässt, setzt diese methode den knoten y* zwischen yp und dessen parent
void Tree::attachYStar(TreeNode* yp, TreeNode* parentOfYp) {
    TreeNode* yStar;

    //schauen ob beim Parent yp links oder rechts ist. dann ersetzen durch y*
    if (parentOfYp->getLeft() == yp) {
        parentOfYp->setLeft(yStar);
    }
    if (parentOfYp->getRight() == yp) {
        parentOfYp->setRight(yStar);
    }

    //in y* dann wieder auf yp verweisen. (ehrlich gesagt, gerade nicht sicher ob links oder rechts relevant ist...)
    yStar->setRight(yp);


    //je nachdem ob yp and y* links oder rechts angehängt wurde, wird an die andere seite der secondary tree angehängt.
    yStar->setLeft(Tree::secondary->getTreeBaseNode());

    //edit:  hab am ende bewusst left und right so verteilt. gedanke dahinter, dass der main tree nach rechts geht.
    //	und da yp zuerst da war, setze ich es als "main" part nach rechts. hoffe da passt.

};

void Tree::findYpAndParent(int max_level) {
    TreeNode* yp;
    TreeNode* yStar;
    TreeNode* parent;
    TreeNode* depthCount = Tree::secondary->getTreeBaseNode();
    int depthOfSecondary = 0;
    int depthOfYp = 0;
    //todo:		yp und parent ausfindig machen.
    //wie?		in T1 mit der Formel die entsprechende höhe ermitteln und dann den Knoten mit dem "minimum weight" (Maximum frequency?) nehmen.

    //geht durch den Secondary Tree um dessen tiefe zu bestimmen.
    while (depthCount->isRightSet()) {
        depthOfSecondary++;
        depthCount = depthCount->getRight();
    }

    depthOfYp = max_level - depthOfSecondary - 1;

    //sonderfall, bei dem y* oben an den baum gesetzt wird.	(kein parent vorhanden... ja, hier stelle ich gerade die bennenung der methode in frage^^)
    if (depthOfYp == 0) {
        yStar->setLeft(Tree::secondary->getTreeBaseNode());
        yStar->setRight(treeBaseNode);
    }
    else {

        //parent mit baum wurzel initialisieren, und dann immer durch die tiefere ebene ersetzen.
        parent = treeBaseNode;
        while (depthOfYp > 1) {
            parent = parent->getRight();
            depthOfYp--;
        }

        //yp noch aus dem parent ziehen.
        yp = parent->getRight();

        attachYStar(yp, parent);

    };

};