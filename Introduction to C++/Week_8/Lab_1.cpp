#include <iostream>
using namespace std;

void SwapValues(int& userVal1, int&userVal2) {
   int tempVal = 0; 
   
   tempVal = userVal1;
   userVal1 = userVal2; 
   userVal2 = tempVal; 
   
   cout << userVal1 << ' ' << userVal2 << endl; 
}

int main() {
   int firstInput; 
   int secondInput; 
   
   cin >> firstInput; 
   cin >> secondInput; 
   
   SwapValues(firstInput, secondInput); 

   return 0;
}