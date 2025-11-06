#include <iostream>
using namespace std;

int main() {
   int firstInteger; 
   int secondInteger; 
   int i;
   
   cin >> firstInteger; 
   cin >> secondInteger; 
   
   if (secondInteger < firstInteger)
{
   cout << "Second integer can't be less than the first." << endl; 
}
   else 
{
   for (i = firstInteger; i <= secondInteger; i += 10)
{
   cout << i << " "; 
}
   cout << endl; 
}

   return 0;
}
