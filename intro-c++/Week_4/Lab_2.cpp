#include <iostream>
using namespace std;

int main() {
   int firstInput;
   int secondInput;
   
   cin >> firstInput;
   cin >> secondInput;
   
   if (firstInput <= secondInput)
{
      while (firstInput <= secondInput) 
   {
      cout << firstInput << " ";
      firstInput += 5;
   }
}

   else 
{
   cout << "Second integer can't be less than the first.";
}
   
   cout << endl; 
   
   return 0;
}
