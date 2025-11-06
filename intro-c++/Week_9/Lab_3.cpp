#include <iostream>
#include <vector>
using namespace std;

bool IsVectorEven (const vector<int> &myVec) {
   bool even = false; 
   unsigned int cnt = 0;
   unsigned int i = 0; 
   
   for (i = 0; i < myVec.size(); ++i) {
      if (myVec.at(i) % 2 == 0) {
         ++cnt; 
      }
   }
   
   if (cnt == myVec.size()) {
      even = true; 
   }
   
   else {
      even = false; 
   }
   
   return even; 
}

bool IsVectorOdd (const vector<int> &myVec) {
   bool odd = false; 
   unsigned int cnt = 0; 
   unsigned int i = 0; 
   
   for (i = 0; i < myVec.size(); ++i) {
      if (myVec.at(i) % 2 == 1) {
         ++cnt; 
      }
   }
   
   if (cnt == myVec.size()) {
      odd = true; 
   }
   
   else {
      odd = false;
   }
   
   return odd; 
}

int main() {
   vector<int> userList; 
   int userSize;
   bool evenCheck;
   bool oddCheck; 
   unsigned int i; 
   
   cin >> userSize; 
   userList.resize(userSize);
   
   for (i = 0; i < userList.size(); ++i) {
      cin >> userList.at(i); 
   }
   
   evenCheck = IsVectorEven (userList);
   oddCheck = IsVectorOdd (userList); 
   
   if ((evenCheck == true) && (oddCheck == false)) {
      cout << "all even" << endl; 
   }
   
   if ((oddCheck == true) && (evenCheck == false)) {
      cout << "all odd" << endl; 
   }
   
   if ((evenCheck == false) && (oddCheck == false)) {
      cout << "not even or odd" << endl; 
   }

   return 0;
}
