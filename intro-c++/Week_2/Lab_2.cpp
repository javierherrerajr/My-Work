#include <iostream>
using namespace std;

int main() {
   double milesPerGallon;
   double dollarsPerGallon;
   double milesPerGallonInput;
   double gasCost; 
   
   cin >> milesPerGallon; 
   cin >> dollarsPerGallon; 
   
   milesPerGallonInput = 10 / milesPerGallon;
   gasCost = milesPerGallonInput * dollarsPerGallon;
   cout << gasCost << " ";

   milesPerGallonInput = 50 / milesPerGallon;
   gasCost = milesPerGallonInput * dollarsPerGallon;
   cout << gasCost << " ";
   
   milesPerGallonInput = 400 / milesPerGallon;
   gasCost = milesPerGallonInput * dollarsPerGallon;
   cout << gasCost << endl;
   return 0;
}
