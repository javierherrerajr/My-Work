#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <string>

using namespace std;

struct Node {
    // holds position of information for the tree
    Node(string); 
    // used to follow AVL Tree properties and yield faster searches in tree
    int height; 
    // holds info being passed in
    string data; 
    // left side of node
    Node* left; 
    // right side of node
    Node* right; 
    // holds parent of the node if the node is not the root
    Node* parent; 
};

#endif // __NODE_H__