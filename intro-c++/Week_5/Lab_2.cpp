#include <iostream>
#include <string>
using namespace std;

int main() {
   string userText;
   int numChar = 0;
   int i;
   
   getline(cin, userText);   

   for (i = 0; i < userText.size(); ++i)
{
   if ((isalpha(userText.at(i))) || (userText.at(i) == '!') || (userText.at(i) == '?'))
{
   numChar++;
}

}

   cout << numChar << endl; 

   return 0;
}
