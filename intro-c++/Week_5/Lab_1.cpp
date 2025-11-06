#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
   string allSpaces; 
   string noSpaces; 
   unsigned int i;
   
   getline (cin, allSpaces);
   
   for (i = 0; i < allSpaces.size(); ++i)
{
   if (allSpaces.at(i) != ' ')
{
   noSpaces = noSpaces + allSpaces;
}

}

   cout << noSpaces << endl; 
   
   return 0;
}