#include <iostream>
#include <string>
using namespace std;

int main() {
   string inputMonth;
   int inputDay;
   
   cin >> inputMonth;
   cin >> inputDay;
   
   if ((inputMonth == "March") && (inputDay >= 1) && (inputDay <= 19))
{
   cout << "winter" << endl; 
}

   else if ((inputMonth == "March") && (inputDay >= 20) && (inputDay <= 31)) 
{
   cout << "spring" << endl; 
}

   else if ((inputMonth == "April") && (inputDay >= 1) && (inputDay <= 30)) 
{
   cout << "spring" << endl; 
}

   else if ((inputMonth == "May") && (inputDay >= 1) && (inputDay <= 31)) 
{
   cout << "spring" << endl; 
}

   else if ((inputMonth == "June") && (inputDay >=1) && (inputDay <= 20)) 
{
   cout << "spring" << endl; 
}

   else if ((inputMonth == "June") && (inputDay >= 21) && (inputDay <= 30)) 
{
   cout << "summer" << endl; 
}

   else if ((inputMonth == "July") && (inputDay >= 1) && (inputDay <= 31)) 
{
   cout << "summer" << endl; 
}

   else if ((inputMonth == "August") && (inputDay >= 1) && (inputDay <= 31)) 
{
   cout << "summer" << endl; 
}

   else if ((inputMonth == "September") && (inputDay >= 1) && (inputDay <= 20)) 
{
   cout << "summer" << endl;
}

   else if ((inputMonth == "September") && (inputDay >= 21) && (inputDay <= 30))
{
   cout << "autumn" << endl;
}

   else if ((inputMonth == "October") && (inputDay >= 1) && (inputDay <= 31)) 
{
   cout << "autumn" << endl; 
}

   else if ((inputMonth == "November") && (inputDay >= 1) && (inputDay <= 30)) 
{
   cout << "autumn" << endl; 
}

   else if ((inputMonth == "December") && (inputDay >= 1) && (inputDay <= 20)) 
{
   cout << "autumn" << endl; 
}

   else if ((inputMonth == "December") && (inputDay >= 21) && (inputDay <= 31)) 
{
   cout << "winter" << endl;
}

   else if ((inputMonth == "January") && (inputDay >= 1) && (inputDay <= 31)) 
{
   cout << "winter" << endl; 
}

   else if ((inputMonth == "February") && (inputDay >= 1) && (inputDay <= 29)) 
{
   cout << "winter" << endl; 
}

   else
{
   cout << "invalid" << endl;
}

   return 0;
}