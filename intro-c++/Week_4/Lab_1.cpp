#include <iostream>
#include <string>
using namespace std;

int main() {
   int integerInput; 

   cin >> integerInput; 
   
   while (integerInput > 0) 
   {
      cout << integerInput % 2;
      integerInput = integerInput / 2; 
   }
   
   cout << endl; 
   
   return 0;
}
