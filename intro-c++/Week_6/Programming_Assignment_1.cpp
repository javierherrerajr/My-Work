#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std; 

int main () {
   
   srand(1000); 
   int userTurns = 0; 
   int userScore = 0;  
   int randNum; 
   int num0 = 0;
   int num20 = 0;
   int num21 = 0; 
   int num22 = 0; 
   int num23 = 0; 
   int num24 = 0; 
   int num25 = 0; 
   bool numOne = false; 
   
   while (userTurns <= 0) {
      cout << "Number of hold-at-20 turn simulations? " << endl; 
      cin >> userTurns; 
         if (userTurns > 0) {
            for (int i = 0; i < userTurns; ++i) {
               while (userScore < 20 && numOne == false) {
               randNum = (rand() % 6) + 1;
               if (randNum == 1) {
                  ++num0; 
                  userScore = 0;  
                  numOne = true; 
               }
               else if (randNum == 2 && numOne == false) {
                     userScore += 2;  
               }
               else if (randNum == 3 && numOne == false) {
                     userScore += 3; 
               }                 
               else if (randNum == 4 && numOne == false) {
                     userScore += 4; 
               }
               else if (randNum == 5 && numOne == false) {
                     userScore += 5;                
               }
               else if (randNum == 6 && numOne == false) {
                     userScore += 6; 
               }
            }
               numOne = false;  
               if (userScore == 20) {
                  ++num20; 
               }
               else if (userScore == 21) {
                  ++num21; 
               }
               else if (userScore == 22) {
                  ++num22; 
               }
               else if (userScore == 23) {
                  ++num23;
               }
               else if (userScore == 24) {
                  ++num24; 
               }
               else if (userScore == 25) {
                  ++num25; 
               }
               userScore = 0; 
            }
         cout << "Score\tEstimated Probability" << endl; 
         cout << "0\t" << fixed << setprecision(6) << static_cast<double>(num0) / userTurns << endl; 
         cout << "20\t" << fixed << setprecision(6) << static_cast<double>(num20) / userTurns << endl;
         cout << "21\t" << fixed << setprecision(6) << static_cast<double>(num21) / userTurns << endl;
         cout << "22\t" << fixed << setprecision(6) << static_cast<double>(num22) / userTurns << endl;
         cout << "23\t" << fixed << setprecision(6) << static_cast<double>(num23) / userTurns << endl;
         cout << "24\t" << fixed << setprecision(6) << static_cast<double>(num24) / userTurns << endl;
         cout << "25\t" << fixed << setprecision(6) << static_cast<double>(num25) / userTurns << endl;
         cout << endl; 
         }
         else {
            cout << "Invalid input. ";
         }
   } 
    return 0;
}