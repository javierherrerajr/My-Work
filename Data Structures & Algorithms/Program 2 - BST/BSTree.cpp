#include "BSTree.h"
#include <iostream>
using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

BSTree::~BSTree() {
    delete root; 
}

bool BSTree::search(const string &node) const{ // searches for the node passed in 
    Node* searching = root;

    while(searching != nullptr && searching->getData() != node){ // searches for where the string is in the BST
        if(searching->getData().compare(node) < 0) { // goes to search right if node is greater
            searching = searching->getRight();
        }

        else { // goes to search left if node is smaller
            searching = searching->getLeft();
        }
    }

    if (searching != nullptr) {
        return true; // the loop found it
    }

    else {
        return false; // the loop didn't find the node
    }
}

string BSTree::smallest() const{ // returns the smallest node if any
    Node* small = root;

    if(small != nullptr) {
        while(small->getLeft()) { // furthest left is the smallest value. Loops to find it.
            small = small->getLeft();
        }
        return small->getData();
    }

    else {
        return ""; //return empty string if empty
    }        
}

string BSTree::largest() const{ // returns the largest node if any
    Node* large = root;

    if(large != nullptr){
        while(large->getRight() != nullptr){ // furthest right is the largest value. Loops to find it. 
            large = large->getRight();
        }
        return large->getData();
    }
    
    else {
        return ""; // return empty string if empty
    }
}

void BSTree::preOrder() const{
    preOrder(root); 
}

void BSTree::inOrder() const{
    inOrder(root);
}

void BSTree::postOrder() const{
    postOrder(root); 
}

void BSTree::preOrder(Node* before) const{ // overloaded function to help with preOrder recursive call
    if(before != nullptr) {
        cout << before->getData() << "(" << before->getCount() <<"), ";
        preOrder(before->getLeft()); // keeps going left until leaf is found
        preOrder(before->getRight()); // goes right once to find other leaf node if any
    }
}

void BSTree::postOrder(Node* after) const{ // overloaded function to help with postOrder recursive call
    if(after != nullptr) {
        postOrder(after->getLeft()); // goes furthest left and starts at leafs
        postOrder(after->getRight()); // gets other leaf node
        cout << after->getData() << "(" << after->getCount() <<"), ";    
    }
}

void BSTree::inOrder(Node* organized) const{ // overloaded function to help with postOrder recursive call
    if(organized != nullptr) {
        inOrder(organized->getLeft());
        cout << organized->getData() << "(" << organized->getCount() <<"), ";
        inOrder(organized->getRight());
    }
}


int BSTree::height(const string &data) const { // returns the height at which a specific string is at
    if(!search(data)) { // base case if the string doesn't exist in the tree
        return -1;
    }

    Node *currentNode = root;
    while(currentNode != nullptr && currentNode->getData() != data) { // searches for string pased in
        if(currentNode->getData().compare(data) < 0) {
            currentNode = currentNode->getRight();
        }

        else {
            currentNode = currentNode->getLeft();
        }
    }

    Node *currLeft = currentNode;
    Node *currRight = currentNode;
    int leftCnt = 0;
    int rightCnt = 0;
    
    if(currentNode->getLeft()) { // checks if string has children
        currLeft = currLeft->getLeft();
        ++leftCnt; // counter used to find the height of the string passed in
        leftCnt += height(currLeft->getData()); // recursive call
    }

    if(currentNode->getRight()) { // checks if string has children
        currRight = currRight->getRight();
        ++rightCnt; // counter used to find the height of the string passed in 
        rightCnt += height(currRight->getData()); // recursive call
    }

    if(leftCnt >= rightCnt) { // checks which side is higher to return the height
        return leftCnt;
    }

    return rightCnt;
}

void BSTree::insert(const string &newString){
    Node* insetion = new Node(newString);
    if(root == nullptr) { // base case for if tree is empty
       root = insetion;
       root->setLeft(nullptr);
       root->setRight(nullptr);
       return;
    }

    Node* curr = root;
    while(curr!= nullptr){
        if(insetion->getData() == curr->getData()) {
           curr->setCount(curr->getCount() + 1);
           return;
        }

       if(insetion->getData().compare(curr->getData()) < 0) { //going to be left of head
                if(curr->getLeft() == nullptr) {
                    curr->setLeft(insetion);
                    break;
                }
                curr = curr->getLeft();
        }

        else {
           if(insetion->getData().compare(curr->getData()) > 0){ // right of head
               if(curr->getRight() == nullptr){ //if empty space for insertion
                   curr->setRight(insetion);
                   break;
               }

               curr = curr->getRight(); //move over to the right
           }
       }
   }
}

void BSTree::remove(const string &data) {

    if (root == nullptr) { // base case for empty tree or if string doesn't exist in tree
        return;
    }

    if ((root->getRight() == nullptr && root->getLeft() == nullptr) && (root->getData() == data)) { // base case if root == data being removed
        if (root->getCount() > 1) {
            root->setCount(root->getCount() - 1);
            return;
        }

        else {
            delete root;
            root = nullptr;
            return;
        }
    }

    remove(root, root, data);
}

void BSTree::remove(Node *parent, Node* curr, string data) { //recursive helper
    if(curr->getData() == data) { //found node we want to remove
        if(curr->getCount() > 1 && curr->getData() != parent->getData()) {
            curr->setCount(curr->getCount() - 1); //removing element that's count is >1
            return;
        }

        if(curr == root && curr->getCount() > 1) { //if node that's found is root and has count >1
            curr->setCount(curr->getCount() - 1);
            return;
        }

        else if(curr->getRight() == nullptr && curr->getLeft() == nullptr) { //if node to be removed was a leaf
            if(curr->getData().compare(parent->getData()) > 0) { //if it was on the right of prev
                parent->setRight(nullptr);
                delete curr;
                return;
            }

            else if(curr->getData() == parent->getData()) { //if equal to prev
                if(parent->getRight() == nullptr){ //if right is already nptr
                    parent->setLeft(nullptr); //delete left
                    delete curr;
                }
                else if(parent->getLeft() == nullptr) { // vice versa ^
                    parent->setRight(nullptr);
                    delete curr;
                }
                else if(parent->getRight() != nullptr && parent->getLeft() != nullptr){ //if both right and left aren't null
                    if(curr->getData() == parent->getLeft()->getData()){  // if equal to left
                        parent->setLeft(nullptr);
                        delete curr;
                    }
                    else if(curr->getData() == parent->getRight()->getData()){//vice versa
                        parent->setRight(nullptr);
                        delete curr;
                    }
                }
            }

            else { //if on left of prev
                parent->setLeft(nullptr);
                delete curr;
                return;
            }
        }

        else if((curr->getLeft() != nullptr && curr->getRight() != nullptr) || (curr->getLeft() != nullptr && curr->getRight() == nullptr)){ //if not a leaf node
            Node* temp = max(curr->getLeft()); //calls max to find largest from that point forward
            curr->setData(temp->getData());
            curr->setCount(temp->getCount());
            remove(curr, curr->getLeft(), curr->getData());
        }

        else if(curr->getLeft() == nullptr && curr->getRight() != nullptr){ //if left u want to find min
            Node *temp = min(curr->getRight());
            curr->setData(temp->getData());
            curr->setCount(temp->getCount());
            remove(curr, curr-> getRight(), curr->getData());
        }
    }

    else if(curr->getData().compare(data) < 0) { // if node is less than root
        remove(curr, curr->getRight(), data);
    }

    else { //greater than root
        remove(curr, curr->getLeft(), data);
    }
}

Node * BSTree::min(Node *curr)const { //smallest within the subtree
    Node *min = curr;

    while(curr != nullptr) {
        min = curr;
        curr = curr->getLeft();
    }

    return min;
}

Node * BSTree::max(Node *curr)const { //largest within subtree
    Node *max = curr;

    while(curr != nullptr) {
        max = curr;
        curr = curr->getRight();
    }
    return max;
}