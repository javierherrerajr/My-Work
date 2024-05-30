#include <iostream>
#include <string>
using namespace std;

int main() {
   string s; 
   unsigned int i;
   
   getline (cin, s); 
   
   while (s != "Quit" && s != "quit" && s != "q")
{
   for (i = s.size(); i > 0; --i)
{
   cout << s.at(i - 1); 
}
   getline (cin, s);
   
   cout << endl;
}

   return 0;
}
