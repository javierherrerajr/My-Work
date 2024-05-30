#include <iostream>
using namespace std;

int CountCharacters(char userChar, const string &userString) {
   int cnt = 0; 
   
   for (unsigned int i = 0; i < userString.size(); ++i) {
      if (userString.at(i) == userChar) {
         ++cnt;
      }
   }
   
   return cnt; 
}

int main() {
   char letter; 
   string userS; 
   
   cin >> letter; 
   getline(cin, userS); 
   
   cout << CountCharacters(letter, userS) << endl; 

   return 0;
}
