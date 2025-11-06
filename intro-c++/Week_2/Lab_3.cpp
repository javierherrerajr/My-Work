#include <iostream>
using namespace std;

int main() {
   double ageYears; 
   double weightPounds; 
   double heartBpm; 
   double timeMinutes; 
   double caloriesBurnedMen; 
   double caloriesBurnedWomen;
   
   cin >> ageYears;
   cin >> weightPounds;
   cin >> heartBpm;
   cin >> timeMinutes;
   
   caloriesBurnedMen = ((ageYears * 0.2017) - (weightPounds * 0.09036) + (heartBpm * 0.6309) - 55.0969) * timeMinutes / 4.184;
   cout << "Men: " << caloriesBurnedMen << " calories" << endl;
   
   caloriesBurnedWomen = ((ageYears * 0.074) - (weightPounds * 0.05741) + (heartBpm * 0.4472) - 20.4022) * timeMinutes / 4.184;
   cout << "Women: " << caloriesBurnedWomen << " calories" << endl; 

   return 0;
}
