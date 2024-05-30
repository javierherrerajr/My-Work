#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string CreateAcronym(const string &userPhrase) {
   string newPhrase; 
   for (unsigned int i = 0; i < userPhrase.size(); ++i) {
      if (isupper(userPhrase.at(i))) {
         newPhrase = newPhrase + userPhrase.at(i);
      }
   }
   
   return newPhrase;
}

int main() {
   string userInput; 
   
   getline(cin, userInput); 
   
   cout << CreateAcronym(userInput) << endl; 

   return 0;
}