#include <iostream>
using namespace std;

int main() {
   int inputYear;
   bool isLeapYear = false;
   
   cin >> inputYear;
   
   isLeapYear = ((inputYear % 4 == 0) || (inputYear % 400 == 0)) && (inputYear != 1900);
   
   if (isLeapYear) {
      cout << inputYear << " is a leap year." << endl;
   }
   
   else {
      cout << inputYear << " is not a leap year." << endl; 
   }
   
   return 0;
}