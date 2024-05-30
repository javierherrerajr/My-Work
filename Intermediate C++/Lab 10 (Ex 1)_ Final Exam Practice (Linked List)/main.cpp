#include <iostream>
#include "IntList.h"

using namespace std;

int main() {
   cout << "Enter a test case #: ";
   int testCase;
   cin >> testCase;
   cout << endl;

   if (testCase == 0) {
      IntList il;
      il.push_front(7);
      il.push_front(6);
      il.push_front(5);
      cout << "Before: " << il << endl;
      il.swapHeadAndTail();
      cout << "After: " << il << endl;
   } 
   else if (testCase == 1) {
      IntList il;
      cout << "Before: " << il << endl;
      il.swapHeadAndTail();
      cout << "After: " << il << endl;
   } 
   else if (testCase == 2) {
      IntList il;
      il.push_front(-1);
      cout << "Before: " << il << endl;
      il.swapHeadAndTail();
      cout << "After: " << il << endl;
   } 
   else if (testCase == 3) {
      IntList il;
      il.push_front(-1);
      il.push_front(-2);
      il.push_front(-3);
      il.push_front(-4);
      il.push_front(-5);
      il.push_front(9);
      il.push_front(2);
      il.push_front(1);
      il.push_front(9);
      cout << "Before: " << il << endl;
      il.swapHeadAndTail();
      cout << "After: " << il << endl;
   } 
   else if (testCase == 4) {
      IntList il;
      il.push_front(-1);
      il.push_front(-2);
      il.push_front(-3);
      il.push_front(-4);
      il.push_front(-5);
      il.push_front(9);
      il.push_front(2);
      il.push_front(1);
      il.push_front(9);
      cout << "Before: " << il << endl;
      il.swapHeadAndTail();
      il.swapHeadAndTail();
      cout << "After: " << il << endl;
   } 
   else if (testCase == 5) {
      IntList il;
      for (int i = 1; i < 100; ++i) {
         il.push_front(5 * i * (i & 1 ? 1: -1));
      }
      cout << "Before: " << il << endl;
      // We should get the same result as 1 swap after 101 swaps
      for (int i = 0; i < 101; ++i) {
         il.swapHeadAndTail();
      }
      cout << "After: " << il << endl;
   }
}
