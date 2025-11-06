#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>

using namespace std;

class Node {
    public:
        Node(string); // constructor that creates node
    // setters
        void setData(string);// gives private variable data a value
        void setLeft(Node*); // gives private pointer left somewhere to point to 
        void setRight(Node*); // gives private pointer right somewhere to point to 
        void setCount(int); // gives private variable count a level to stay in the BST
    // getters
        string getData() const; // returns data from node
        Node* getLeft() const; // returns left side of node or leaf
        Node* getRight() const; // returns right side of node or leaf
        int getCount() const; // returns level at which the node is located at in the BST
    private:
        string data; // holds user data
        int count; // holds the level the node is currently at
        Node *left; // holds the left subtree
        Node *right; // holds the right subtree
};

#endif