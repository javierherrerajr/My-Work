#include <fstream>
#include <iostream>
#include <cstdlib> //needed for exit function
using namespace std;

int fileSum (string s) {
   int total = 0;
   int num;   
   ifstream inFS; 

   inFS.open (s);

   if (!inFS.is_open()) {
      cout << "Error opening " << s << endl; 

      exit(1); 
   }
   
   while (inFS >> num) {
      total += num; 
   }

   inFS.close(); 

   return total; 
}

int main() {

   string filename;
   int sum = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   
   sum = fileSum(filename);

   cout << "Sum: " << sum << endl;
   
   return 0;
}

// Place fileSum implementation here