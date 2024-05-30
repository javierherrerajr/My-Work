#include <iostream>
#include "IntList.h"

using namespace std;

IntList::IntList(){
    head = nullptr;
    tail = nullptr; 
}

IntList::IntList(const IntList &cpy){
    head = nullptr;
    tail = nullptr;
    if (cpy.head == nullptr) {
        head = nullptr;
        tail = nullptr;
    }
    else {
        for (IntNode *curr = cpy.head; curr != nullptr; curr = curr -> next) {
            push_back(curr->data);
        }
    }   
}

IntList::~IntList(){
    clear();
}

void IntList::push_front(int value){
    if (empty() == true){
        head = new IntNode(value);
        tail = head;
    }
    else{
        IntNode *temp = new IntNode(value);
        temp->next = head;
        head = temp;
    }
}

void IntList::push_back(int value){
    if (tail == nullptr){
        tail = new IntNode(value);
        head = tail;
    }
    else{
        IntNode *temp = new IntNode(value);
        tail->next = temp;
        tail = temp;
    }
}

void IntList::pop_front(){
    if (empty() == false){
        if (head == tail){
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else{
            IntNode *temp = head->next;
            delete head;
            head = temp;
        }
    }
}

bool IntList::empty() const{
    bool isZero = false; 
    if (head == nullptr && tail == nullptr){
        isZero = true; 
    }

    return isZero; 
}

void IntList::clear(){
    while(empty() == false){
        pop_front();
    }
}

const int & IntList::front() const{
    return head->data;
}

const int & IntList::back() const{
    return tail->data;
}

void IntList::selection_sort(){
    for (IntNode *i = head; i != nullptr; i = i->next){
        IntNode *minLoc = i;
        for (IntNode *j = (i->next); j != nullptr; j = (j->next)){
            if((j->data) < (minLoc->data)){
                minLoc = j;
            }
        }
        int temp = minLoc->data;
        minLoc->data = i->data;
        i->data = temp;
    }
}

void IntList::insert_ordered(int value){
    IntNode *newVal = new IntNode(value);
    if (head == nullptr) {
        push_front(value);
        return;
    }

    if (newVal -> data <= (head -> data)) {
        push_front(value);
        delete newVal;
        return;
    }

    if (newVal -> data >= (tail -> data)) {
        push_back(value);
        delete newVal;
        return;
    }

    for (IntNode *prev = head; prev != nullptr; prev = prev -> next) {
        IntNode *curr = prev -> next;
        if (value <= (curr -> data) && value >= (prev -> data)) {
            prev -> next = newVal;
            newVal -> next = curr;
            return;
        }
    }
    return;
}

void IntList::remove_duplicates(){
    if ((!empty()) && (head != tail)){
        for (IntNode* i = head; i != 0; i = i->next){
            IntNode *prev = i;
            for (IntNode *j = (i->next); j != 0; j = (j->next)){
                if((j->data) == (i->data)){
                    if (j == tail){
                        delete j;
                        tail = prev;
                        tail->next = nullptr;
                        j = prev;
                    }
                    else{
                        prev->next = j->next;
                        delete j;
                        j = prev;
                    }
                }
                else{
                    prev = prev->next;
                }
            }
        }
    }
}

IntList & IntList::operator=(const IntList &rhs){
    if (this != &rhs){
        clear();
        IntNode *curr = rhs.head;
        while (curr != 0){
            push_back(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}

ostream & operator<<(ostream & o, const IntList & value){
    IntNode *currNode = value.head;
    while (currNode != nullptr) {
        o << currNode -> data;

        if (currNode -> next != nullptr) {
            o << " ";
        }
        currNode = currNode -> next;
    }
    return o;
}