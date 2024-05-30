#include <iostream>
#include <vector>
#include <string>
using namespace std;

string GetPhoneNumber (const vector<string> &nameVec, const vector<string> &phoneNumberVec, const string &contactName) {
   unsigned int i;
   string num;
   
   for (i = 0; i < nameVec.size(); ++i) { 
      if (nameVec.at(i) == (contactName)){
         num = phoneNumberVec.at(i);
      }
   }
   return num;
}

int main() {
   vector<string> name; 
   vector<string> number; 
   string currentNum; 
   string contact; 
   int n; 
   int i; 
   
   cin >> n; 
   name.resize(n); 
   number.resize(n); 
   
   for (i = 0; i < n; ++i) {
      cin >> name.at(i); 
      cin >> number.at(i); 
   }
   
   cin >> contact; 
   currentNum.append(GetPhoneNumber (name, number, contact));
   
   cout << currentNum << endl; 

   return 0;
}
