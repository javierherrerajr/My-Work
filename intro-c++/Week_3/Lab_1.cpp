#include <iostream>
using namespace std;

int main() {
   int firstInput;
   int secondInput;
   int thirdInput;
   int firstOutput;
   int secondOutput;
   int thirdOutput; 
   
   cin >> firstInput; 
   cin >> secondInput; 
   cin >> thirdInput; 
   
   firstOutput = (firstInput > secondInput) && (firstInput > thirdInput);
   secondOutput = (secondInput > firstInput) && (secondInput > thirdInput);
   thirdOutput = (thirdInput > firstInput) && (thirdInput > secondInput); 
   
   if (firstOutput) {
      cout << firstInput << endl; 
   }
   
   else if (secondOutput) { 
      cout << secondInput << endl; 
   }
   
   else if (thirdOutput) {
      cout << thirdInput << endl; 
   }
   
   else {
      cout << firstInput << endl; 
   }
   return 0;
}