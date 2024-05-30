#ifndef INTLIST_H
#define INTLIST_H
#include <iostream>

using namespace std; 

struct IntNode {
    int data; 
    IntNode *prev; 
    IntNode *next;
    IntNode (int data) : data(data), prev(nullptr), next(nullptr) {}
};

class IntList {
    public: 
        IntList() : dummyHead(new IntNode(0)), dummyTail(new IntNode(0)) {dummyHead->next = dummyTail; dummyTail->prev = dummyHead;}
        ~IntList(); 
        void push_front(int value);
        void pop_front(); 
        void push_back(int value);
        void pop_back(); 
        bool empty() const; 
        friend ostream & operator<<(ostream &out, const IntList &rhs);
        void printReverse() const; 
    private:
        IntNode *dummyHead;
        IntNode *dummyTail; 
};

#endif