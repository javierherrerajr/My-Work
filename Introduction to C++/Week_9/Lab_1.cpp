#include <iostream>
#include <vector>
using namespace std;

void PrintValidIntegers (vector<int>& list, vector<int>& range) {
   
   for (unsigned int i = 0; i < list.size(); ++i) { 
      if ((list.at(i) >= range.at(0)) && (list.at(i) <= range.at(1))) {
         cout << list.at(i) << ' ';
      }
   }
   
   cout << endl;
}

int main() {
   const int CONSTANT_RANGE = 2;
   vector<int> userList; 
   vector<int> userRange (CONSTANT_RANGE); 
   int userSize;
   int i;
   
   cin >> userSize;
   userList.resize (userSize);
   
   for (i = 0; i < userSize; ++i) {
      cin >> userList.at(i); 
   }
   
   for (i = 0; i < CONSTANT_RANGE; ++i) {
      cin >> userRange.at(i);
   }
   
   PrintValidIntegers (userList, userRange);

   return 0;
}
