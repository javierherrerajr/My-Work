#include <iostream>
using namespace std;

int LargestNumber(int num1, int num2, int num3) {
   int large = 0; 
   
   if ((num1 > num2) && (num1 > num3)) {
      large = num1;
   }
   else if ((num2 > num1) && (num2 > num3)) {
      large = num2; 
   }
   else {
      large = num3;  
   }
     
   return large;
}

int SmallestNumber(int num1, int num2, int num3) {
   int small = 0; 
   
   if ((num1 < num2) && (num1 < num3)) {
      small = num1;
   }
   else if ((num2 < num1) && (num2 < num3)) {
      small = num2; 
   }
   else {
      small = num3;  
   }
   
   return small;
}

int main() {
   int numOne;
   int numTwo;
   int numThree; 
   int smallNum; 
   int largeNum; 
   
   cin >> numOne; 
   cin >> numTwo; 
   cin >> numThree;
   
   smallNum = SmallestNumber(numOne, numTwo, numThree);
   largeNum = LargestNumber(numOne, numTwo, numThree); 
   
   cout << "largest: " << largeNum << endl; 
   cout << "smallest: " << smallNum << endl; 

   return 0;
}
