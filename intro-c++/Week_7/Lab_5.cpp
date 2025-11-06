#include <iostream>
using namespace std;

bool IsLeapYear(int year) {
   bool leap = false; 
   
   if(year % 4 == 0) {
      leap = true; 
   }
   if(year % 100 == 0){
      leap=false;
   }
   if(year % 400 == 0){
      leap=true;
   }

   return leap;
}

int main() {
   int yearInput;
   bool leapFunction; 
   
   cin >> yearInput; 
   leapFunction = IsLeapYear(yearInput); 
   
   if (leapFunction == true) {
      cout << yearInput << " is a leap year." << endl; 
   }
   else {
      cout << yearInput << " is not a leap year." << endl; 
   }
   
   return 0;
}
