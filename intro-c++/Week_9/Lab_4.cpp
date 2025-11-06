#include <iostream>
#include <vector> 
#include <string>
using namespace std;

int GetFrequencyOfWord (const vector<string> &wordsList, string currWord) {
   unsigned int i; 
   int frequency = 0;
   
   for (i = 0; i < wordsList.size(); ++i) {
      if (wordsList.at(i) == currWord) {
         ++frequency;
      }
   }
   
   return frequency; 
}

int main() {
   vector<string> userList; 
   vector<int> frequency;
   int userSize; 
   string currentWord; 
   unsigned int i;
   
   cin >> userSize; 
   userList.resize (userSize); 
   frequency.resize (userSize); 
   
   for (i = 0; i < userList.size(); ++i) {
      cin >> userList.at(i); 
   }
   
   for (i = 0; i < userList.size(); ++i) {
      currentWord = userList.at(i);
      frequency.at(i) = GetFrequencyOfWord(userList, currentWord);
   }
   
   for (i = 0; i < userList.size(); ++i) {
      cout << userList.at(i) << " " << frequency.at(i) << endl;
   }
   
   return 0;
}
