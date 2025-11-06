#include <iostream>
using namespace std;

int main() {
   int highwayNumber;
   
   cin >> highwayNumber;

   if (((highwayNumber >= 1) && (highwayNumber <= 99)) && (highwayNumber % 2 == 0)){
      cout << "The " << highwayNumber << " is primary, going east/west." << endl; 
   }
   
   else if ((highwayNumber >= 1) && (highwayNumber <= 99)) {
      cout << "The " << highwayNumber << " is primary, going north/south." << endl;
   }
   
   else if (((highwayNumber >= 100) && (highwayNumber <= 999)) && (highwayNumber % 2 == 0)){
      cout << "The " << highwayNumber << " is auxiliary, serving the " << highwayNumber % 100 << ", going east/west." << endl;
   }
   
   else if ((highwayNumber >= 100) && (highwayNumber <= 999)) {
      cout << "The " << highwayNumber << " is auxiliary, serving the " << highwayNumber % 100 << ", going north/south." << endl;
   }
   
   else {
      cout << highwayNumber << " is not a valid interstate highway number." << endl; 
   }
   return 0;
}
