#include <iostream>
using namespace std;

void RemoveSpaces(string &userString) { 
   
   for (unsigned int i = 0; i < userString.size(); ++i) {
      while (userString.at(i) == ' ') {
         userString.replace(i, 1, ""); 
      }
   }
   
   cout << userString << endl;
}

int main() {
   string userInput; 
   
   getline(cin, userInput); 
   
   RemoveSpaces(userInput); 

   return 0;
}
