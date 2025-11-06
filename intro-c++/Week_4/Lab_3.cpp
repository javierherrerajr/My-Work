#include <iostream>
using namespace std;

int main() {
   int firstInput;
   
   cin >> firstInput; 
   if ((firstInput >= 11) && (firstInput <= 100)) 
{
   cout << firstInput << " ";
   while (firstInput % 11 != 0)
{
   firstInput -= 1; 
   cout << firstInput << " "; 
}

}

   else 
{
   cout << "Input must be 11-100";
}

   cout << endl; 

   return 0;
}
