#include "Node.h"

// constructs an empty node for tree
Node::Node(string data) {
    height = 0; 
    this->data = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr; 
}