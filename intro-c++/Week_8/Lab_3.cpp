#include <iostream>
#include <string>
using namespace std;

void IntegerToReverseBinary(int integerValue, string &s) {
   int temp; 
   
   while(integerValue > 0) {
      temp = integerValue % 2; 
      if(temp == 1) {
         s = s+"1";  
      }
      else {
         s = s+"0";  
      }
      integerValue /= 2;
   }
}

void PrintReverseString(const string &userString) {
   int n = userString.size();
   n = n - 1;
   while(n >= 0) {
      cout<<userString.at(n);
      n = n - 1; 

   }
   cout<<endl;
}

int main() {
   int userInput;
   string userS;
   
   cin >> userInput; 
   
   IntegerToReverseBinary(userInput, userS); 
   
   PrintReverseString(userS); 

   return 0;
}
