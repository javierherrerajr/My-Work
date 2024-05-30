#include <iostream>
#include <cmath>
using namespace std;

int MaxMagnitude(int userVal1, int userVal2) {
   int maxVal = 0;
   
   if (abs(userVal1) > abs(userVal2)) {
      maxVal = userVal1; 
   }
   else {
      maxVal = userVal2;
   }
   
   return maxVal; 
}

int main() {
   int num1; 
   int num2; 
   int maxMag;
   
   cin >> num1; 
   cin >> num2;
   
   maxMag = MaxMagnitude(num1, num2); 
   
   cout << maxMag << endl; 

   return 0;
}
