#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
   srand(0);
   int userInput = 1;
   int randomNum; 
   
   while (userInput == 1)
{
   randomNum = (rand() % 4) + 1;
   if (randomNum == 1)
{
   cout << "pig "; 
}
   if (randomNum == 2) 
{ 
   cout << "cow "; 
}
   if (randomNum == 3) 
{ 
   cout << "chicken "; 
}
   if (randomNum == 4)
{
   cout << "horse ";
}  
   cin >> userInput;
}

   cout << endl; 

   return 0;
}
