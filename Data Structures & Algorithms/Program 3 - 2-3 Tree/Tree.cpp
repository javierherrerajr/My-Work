#include "Tree.h"
#include <iostream>

using namespace std;

// constructor for Tree
Tree::Tree() {
    root = nullptr;
}

// destructor that calls recursive helper
Tree::~Tree() {
    delete recurDelete(root);
}

// inserts new node into tree following all properties accordingly 
void Tree::insert(const string &str) {
    if (root == nullptr) { // base case if tree is empty
        root = new Node();
        root->small = str;
        return; 
    }
    // Recursive down until we encounter a leaf
    Node* targetNode = root;
    while (targetNode->left != nullptr) {
        // Get the order of the string relative to small and (if exists) large to find which Node to travel to
        if (targetNode->hasTwoStrings()) {
            if (targetNode->small.compare(str) > 0) {
                targetNode = targetNode->left;
            }

            else if (targetNode->large.compare(str) < 0) {
                targetNode = targetNode->right;
            }

            else {
                targetNode = targetNode->middle;
            }
        }

        else {
            if (targetNode->small.compare(str) > 0) {
                targetNode = targetNode->left;
            }

            else {
                targetNode = targetNode->middle;
            }
        }
    }

    if (targetNode->hasTwoStrings()) {
        // Find the small, middle, and large string of the three
        // Split up the three into the target node with middle string and two new leaf nodes as its children
        string small;
        string middle;
        string large;

        if (targetNode->small.compare(str) > 0) {
            small = str;
            middle = targetNode->small;
            large = targetNode->large;
        }

        else {
            small = targetNode->small;

            if (targetNode->large.compare(str) < 0) {
                middle = targetNode->large;
                large = str;
            }

            else {
                middle = str;
                large = targetNode->large;
            }
        }

        Node* smallNode = new Node();
        smallNode->small = small;
        Node* largeNode = new Node();
        largeNode->small = large;

        targetNode->small = middle;
        targetNode->large = ""; // assign empty
        targetNode->left = smallNode;
        targetNode->middle = largeNode;
        targetNode->right = nullptr; // might be redundant

        smallNode->parent = targetNode;
        largeNode->parent = targetNode;

        // Time to do some shifting
        shiftUp(targetNode);
    }

    else {
        // The node has 1 string in it, find if it should be inserted into the left or right
        if (targetNode->small.compare(str) > 0) {
            // Put str in the small area and bring small up to large
            targetNode->large = targetNode->small;
            targetNode->small = str;
        }

        else {
            // Put str in the large area
            targetNode->large = str;
        }
    }
}

// calls recursive helper to traverse
void Tree::preOrder() const {
    preOrderHelper(root);
    cout << endl; 
}

// calls recursive helper to traverse in order
void Tree::inOrder() const {
    inOrderHelper(root);
    cout << endl; 
}

// calls recursive helper to traverse in post order
void Tree::postOrder() const {
    postOrderHelper(root);
    cout << endl; 
}

// removes node with matching key
void Tree::remove(const string &str) {
    Node* searchNode = root;
    while (searchNode != nullptr) {
        // Compare small and (possibly) large
        if (searchNode->small == str || (searchNode->hasTwoStrings() && searchNode->large == str)) {
            break;
        }

        else { // Re-assign searchNode with possible children
            if (searchNode->small.compare(str) > 0) {
                // Go to the left
                searchNode = searchNode->left;
            }

            else {
                if (searchNode->hasTwoStrings() && searchNode->large.compare(str) < 0) {
                    // The string we're searching for is larger than both strings, go to right
                    searchNode = searchNode->right;
                }

                else {
                    // There is only one child or it's in-between two children, go to the middle (right)
                    searchNode = searchNode->middle;
                }
            }
        }
    }

    if (searchNode != nullptr) {
        if (searchNode->hasTwoStrings()) {
            if (str == searchNode->small) {
                searchNode->small = searchNode->large;
                searchNode->large = "";
            }

            else {
                searchNode->large = "";
            }
        }

        else {
            Node* parent = searchNode->parent;
            if (parent != nullptr) {
                if (str.compare(parent->small) < 0) {
                    parent->left = nullptr;
                    parent->large = parent->middle->small;
                    parent->middle = nullptr;
                } else {
                    parent->middle = nullptr;
                    parent->large = parent->small;
                    parent->small = parent->left->small;
                    parent->left = nullptr;
                }
            }

            else {
                Node* succNode = new Node();
                if (root->left != nullptr) {
                    succNode->small = root->left->small;
                    succNode->large = root->middle->small;
                    root = succNode;
                } 
                
                else {
                    root = nullptr;
                }
            }
        }
    }
}

// searches for node that has matching key passed in
bool Tree::search(const string &str) const {
    Node* searchNode = root;
    while (searchNode != nullptr) {
        // Compare small and (possibly) large
        if (searchNode->small == str || (searchNode->hasTwoStrings() && searchNode->large == str))  {
            return true;
        }

        else { // Re-assign searchNode with possible children
            if (searchNode->small.compare(str) > 0) {
                // Go to the left
                searchNode = searchNode->left;
            }

            else {
                if (searchNode->hasTwoStrings() && searchNode->large.compare(str) < 0) {
                    // The string we're searching for is larger than both strings, go to right
                    searchNode = searchNode->right;
                }

                else {
                    // There is only one child or it's in-between two children, go to the middle (right)
                    searchNode = searchNode->middle;
                }
            }
        }
    }

    return false;
}

// shifts up node passed in accordingly 
void Tree::shiftUp(Node *node) {
    // The node provided in this function needs to be moved into its parent and ALWAYS has only 1 node
    // Therefore, if there is no parent, we shouldn't do anything
    // Only run if the parent is valid
    if (node->parent != nullptr) {
        Node* parent = node->parent;
        if (parent->hasTwoStrings()) { // This is our recursive case!
            // Three cases: the node's string is smaller, in the middle, or larger than the node's two strings
            if (parent->small.compare(node->small) > 0) { // Node is coming from the LEFT
                Node* newLarge = new Node();
                // newLarge takes the parent's middle and right children
                newLarge->left = parent->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->right;
                newLarge->middle->parent = newLarge;
                newLarge->small = parent->large;

                // Reset values of parent and insert the value from node
                parent->left = node; // The new small is the node itself, intact
                parent->middle = newLarge;
                parent->right = nullptr;
                // parent's small stays as parent's small
                parent->large = ""; // Reset to empty

                // Complete the chain by linking newLarge's parent value up
                newLarge->parent = parent;
            }

            else if (parent->large.compare(node->small) < 0) { // Node is coming from the RIGHT
                Node* newSmall = new Node();
                // newSmall takes the parent's left and middle children
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = parent->middle;
                newSmall->middle->parent = newSmall;
                newSmall->small = parent->small;

                // Reset values of parent and insert the value from node
                parent->left = newSmall;
                parent->middle = node; // The new large is the node itself, intact
                parent->right = nullptr;
                parent->small = parent->large;
                parent->large = ""; // Reset to empty

                // Complete the chain by linking newSmall's parent value up
                newSmall->parent = parent;
            }

            else { // Node is coming from the MIDDLE
                Node* newSmall = new Node();
                newSmall->small = parent->small;
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = node->left;
                newSmall->middle->parent = newSmall;

                Node* newLarge = new Node();
                newLarge->small = parent->large;
                newLarge->left = node->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->middle;
                newLarge->middle->parent = newLarge;

                // Reset values of parent and insert the value from node
                parent->left = newSmall;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->small = node->small;
                parent->large = ""; // Reset to empty

                // Complete the chain by linking newSmall and newLarge's parent values up
                newSmall->parent = parent;
                newLarge->parent = parent;

                delete node; // Delete node as it is now unneeded
            }

            shiftUp(parent);
        }

        else { // Moving up into the same node, dealing with children (base case!)
            if (parent->small > node->small) { // node is coming from the left side
                parent->large = parent->small;
                parent->small = node->small;

                // Since the node's string is smaller, the node's left and middle are placed onto the parent's left and middle
                // The parent's middle is the remaining child that needs to be assigned onto the parent's right
                parent->left = node->left;
                parent->right = parent->middle;
                parent->middle = node->middle;
            }

            else { // node is coming from the middle (right)
                parent->large = node->small;

                // Since the node's string is larger, the node's left and middle are placed onto the parent's middle and right
                // The parent's left is the remaining child, and it doesn't need to be moved
                parent->middle = node->left;
                node->left->parent = parent;
                parent->right = node->middle;
                node->middle->parent = parent;
            }

            // Update both the parent pointers and delete the now useless node
            node->left->parent = parent;
            node->middle->parent = parent;
            delete node;
        }
    }
}

// destructor that deallocates all pointers correctly 
Node *Tree::recurDelete(Node *node) {
    if (node != nullptr) {
        delete recurDelete(node->left);
        delete recurDelete(node->middle);
        delete recurDelete(node->right);
    }

    return node;
}

// recursive helper function that traverses tree in preOrder notation
void Tree::preOrderHelper(Node *node) const {
    if (node != nullptr) {
        if (node->hasTwoStrings()) {
            // SM LE LA MI RI
            cout << node->small << ", ";
            preOrderHelper(node->left);
            cout << node->large << ", ";
            preOrderHelper(node->middle);
            preOrderHelper(node->right);
        }

        else {
            cout << node->small << ", ";
            preOrderHelper(node->left);
            preOrderHelper(node->middle);
        }
    }
}

// recursive helper function that traverses tree inOrder notation
void Tree::inOrderHelper(Node *node) const {
    if (node != nullptr) {
        inOrderHelper(node->left);
        cout << node->small << ", ";
        inOrderHelper(node->middle);

        // There are two strings in the node
        if (node->hasTwoStrings()) {
            cout << node->large << ", ";
            inOrderHelper(node->right);
        }
    }
}

// recursive helper function that traverses tree in postOrder notation
void Tree::postOrderHelper(Node *node) const {
    if (node != nullptr) {
        if (node->hasTwoStrings()) {
            // LE MI SM RI LA
            postOrderHelper(node->left);
            postOrderHelper(node->middle);
            cout << node->small << ", ";
            postOrderHelper(node->right);
            cout << node->large << ", ";
        }

        else {
            postOrderHelper(node->left);
            postOrderHelper(node->middle);
            cout << node->small << ", ";
        }
    }
}  