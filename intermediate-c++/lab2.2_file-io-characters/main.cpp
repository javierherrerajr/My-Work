#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

// Place charCnt prototype (declaration) here
int charCnt (string s, char c) {
   int cnt = 0; 
   char ch; 
   ifstream fin; 

   fin.open (s); 

   if (!fin.is_open()) {
      cout << "Error opening " << s << endl; 

      exit(1); 
   }
   
   while (fin.get(ch)) {
      if (c == ch) {
         ++cnt; 
      }
   }

   fin.close(); 

   return cnt; 
}

int main() {
   string filename;
   char ch;
   int chCnt = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   cout << "Enter a character: ";
   cin.ignore(); // ignores newline left in stream after previous input statement
   cin.get(ch);
   cout << endl;

   chCnt = charCnt(filename, ch);   
   cout << "# of " << ch << "'s: " << chCnt << endl;
   
   return 0;
}

// Place charCnt implementation here
