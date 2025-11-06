#include <iostream>
using namespace std;

double StepsToMiles(int userSteps) {
   double stepsPerMile; 
   
   stepsPerMile = userSteps / 2000.0; 
   
   return stepsPerMile; 
}

int main() {
   int steps; 
   double miles; 
   
   cin >> steps; 
   miles = StepsToMiles(steps);
   
   cout << miles << endl; 

   return 0;
}
