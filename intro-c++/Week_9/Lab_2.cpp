#include <iostream>
#include <vector> 
using namespace std;

int GetMinimumInt (const vector<int> &listInts) {
   int minVal = listInts.at(0);
   unsigned int i; 
   
   for (i = 0; i < listInts.size(); ++i) {
      if (listInts.at(i) < minVal) {
         minVal = listInts.at(i);
      }
   }
   
   return minVal;
}

int main() {
   vector<int> userList;
   int userSize;
   int userMin;
   unsigned int i; 
   
   cin >> userSize; 
   userList.resize (userSize); 
   
   if (userSize < 20) {
      for (i = 0; i < userList.size(); ++i) {
         cin >> userList.at(i); 
      }
   }
   
   userMin = GetMinimumInt (userList);
   
   for (i = 0; i < userList.size(); ++i) {
      userList.at(i) -= userMin; 
      cout << userList.at(i) << ' ';
   }
   
   cout << endl;
   
   return 0;
}
