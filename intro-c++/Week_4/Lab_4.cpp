#include <iostream>
using namespace std;

int main() {
   int positiveInput;
   int inputTotal = 0;
   int inputAvg; 
   int inputMax = 0; 
   int cnt = 0;
   
   cin >> positiveInput; 
   
   while (positiveInput >= 0) 
{
   inputTotal += positiveInput;  
   ++cnt ;
   
   if (positiveInput > inputMax) 
{
   inputMax = positiveInput;
}
   cin >> positiveInput; 
}

   inputAvg = inputTotal / cnt; 
   
   cout << inputAvg << " " << inputMax;
   cout << endl; 
   

   return 0;
}
