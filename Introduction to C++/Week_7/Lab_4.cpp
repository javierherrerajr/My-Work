#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

string HeadsOrTails() {
   int randNum;
   randNum=rand()%2;
   string s1; 
   string s2;  
   
   s1 = "heads";
   s2 = "tails";
   if(randNum==0){
      return s1;
   }
   else{
      return s2;
   }
}
   
int main() {  
   int userInput;  
   
   srand(2);

   cin >> userInput; 
   for(unsigned int i=0; i<userInput; ++i)
   {
   
   cout << HeadsOrTails() << endl; 
   }

   return 0;
}