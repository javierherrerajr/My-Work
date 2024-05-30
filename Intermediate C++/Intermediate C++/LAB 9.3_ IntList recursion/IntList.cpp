#include "IntList.h"

#include <ostream>

using namespace std;

IntList::IntList() : head(0) {}


void IntList::push_front(int val) {
   if (!head) {
      head = new IntNode(val);
   } else {
      IntNode *temp = new IntNode(val);
      temp->next = head;
      head = temp;
   }
}

ostream & operator<<(ostream & out, const IntList & list){
    if (list.head == nullptr){
        out << "";
    }
    else{
        IntNode* temp = list.head;
        out << temp;
    }
    return out;
}

ostream & operator<<(ostream & out , IntNode *start){
    if(start != nullptr){
        if(start->next == nullptr){
            out << start->value;
        }
        else{
            IntNode *temp = start->next;
            out << start->value << " " << temp;
        }
    }
    return out;
}

bool IntList::exists(int x) const{
    if(head == nullptr){
        return false;
    }
    else {
        IntNode* temp = head;
        return exists(temp, x);
    }
}

bool IntList::exists(IntNode *start, int match) const{
    if (start->value == match){
        return true;
    }
    else if(start->next == nullptr){
        return false;
    }
    else{
        IntNode* temp = start->next;
        return exists(temp, match);
    }
}