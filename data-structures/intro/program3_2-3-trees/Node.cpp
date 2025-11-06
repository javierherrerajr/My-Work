#include "Node.h"

// contructs empty node
Node::Node() : left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) { }

// returns true if large isn't empty, indicating the node has two strings
bool Node::hasTwoStrings() const {
    return !large.empty();
}