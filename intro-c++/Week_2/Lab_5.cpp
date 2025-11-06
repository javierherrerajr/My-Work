#include <iostream>
#include <cmath>
using namespace std;

int main() {
   long long phoneNumber;
   long long areaCode;
   long long prefix;
   long long lineNumber;

   cin >> phoneNumber;
  
   areaCode = phoneNumber / 10000000;
   prefix = phoneNumber % 10000000 / 10000;
   lineNumber = phoneNumber % 10000;
   
   cout << areaCode << "-" << prefix << "-" << lineNumber << endl;
   
   return 0;
}
