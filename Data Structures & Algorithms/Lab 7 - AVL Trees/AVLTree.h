#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

using namespace std;

class AVLTree {
    private:
        // top of tree
        Node *root;
    private:
        // rotates BST to follow AVL properties
        void rotate(Node*);
        // rotates left side to follow AVL if necessary
        Node* rotateLeft(Node*);
        // rotates right side to follow AVL if necessary
        Node* rotateRight(Node*);
        // prints all the balance factors of each node
        void printBalanceFactors(Node *);
        // constructs dotty file to form graph
        void visualizeTree(ofstream &, Node *);
        // returns the height of the node passed in
        int height(Node*) const;
        // finds and returns closest unbalanced node with a balance factor of 2 or -2
        Node* findUnbalancedNode(Node*); 
    public:
        // constructor
        AVLTree();
        // inserts new nodes to tree accordingly
        void insert(const string &);
        // calculates the balance factor of each node
        int balanceFactor(Node*);
        // calls recursive helper to print all nodes in tree
        void printBalanceFactors();
        // calls recursive helper to create dotty file
        void visualizeTree(const string &);
        // finds parent for new node going to be inserted. 
        Node *InSearch(const string &, Node*) const;
};

#endif // __AVL_TREE_H__