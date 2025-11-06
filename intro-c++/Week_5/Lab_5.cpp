#include <iostream>
#include <string>
using namespace std;

int main() {
   string userString;
   bool hasDigit = true;
   unsigned int i; 
   
   cin >> userString;

   for (i = 0; i < userString.size(); ++i)
{
   if (!isdigit(userString.at(i)))
{
   hasDigit = false; 
}

}
   if (hasDigit) 
{
   cout << "yes" << endl; 
}
   else 
{
   cout << "no" << endl; 
}

   return 0;
}
