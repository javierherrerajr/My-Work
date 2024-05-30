#include "Node.h"

Node::Node(string treeData) {
    data = treeData;
    count = 1; 
    left = nullptr;
    right = nullptr;
}

string Node::getData() const{
    return data;
}

int Node::getCount() const{
    return count;
}

Node* Node::getLeft() const{
    return left; 
}

Node* Node::getRight() const {
    return right; 
}

void Node::setLeft(Node* newNode){
    left = newNode;
}

void Node::setRight(Node* newNode){
    right = newNode;
}

void Node::setData(string str){
    data = str;
}

void Node::setCount(int updatedCount){
    count = updatedCount;
}