#ifndef __INTLIST_H
#define __INTLIST_H

#include <iostream>

using namespace std;

// IntNode struct
// Note: value cannot be changed after initialization
struct IntNode {
   const int value;
   IntNode* next;
   IntNode(int value) : value(value), next(nullptr) {}
};

class IntList {
   IntNode* head;
 public:
   IntList();

   // Inserts a data value to the front of the list.
   void push_front(int);

   void swapHeadAndTail();
  
   friend ostream& operator<<(ostream &out, const IntList &rhs) {
      IntNode *t = rhs.head;
      if (t != nullptr) {
         out << t->value;
         for (t = t->next; t != nullptr; t = t->next) {
            out << " " << t->value;
         }
      }
      return out;
   }
};

#endif /* __INTLIST_H */
