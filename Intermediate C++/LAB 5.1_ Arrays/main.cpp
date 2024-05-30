#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std; 

double mean(const double array[], int arraySize) {
   double avg; 
   double sum = 0.0; 
   double cnt = 0.0; 

   for (int i = 0; i < arraySize; ++i) {
      sum += array[i];
      ++cnt; 
   }

   avg = sum / cnt; 
   
   return avg; 
}

void remove(double array[], int &arraySize, int index) {
   for (int i = index; i < arraySize - 1; ++i) {
      array[i] = array[i + 1]; 
   }

   arraySize -= 1; 
   double newArray[arraySize];

   for (int i = 0; i < arraySize; ++i) {
      cin >> newArray[i]; 
   }

   array = newArray;
}


// - Passes in an array and the size of the array.
// - Outputs each value in the array separated by a comma and space, with no comma, space or newline at the end.
void display(const double array[], int arraySize) {
   for (int i = 0; i < arraySize - 1; ++i) {
      cout << array[i] << ", "; 
   }

   cout << array[arraySize - 1]; 
}


const int ARR_CAP = 100;

int main(int argc, char *argv[]) {
   fstream fin; 
   int removeIndex; 
   
   if (argc != 2) {
      cout << "USAGE: " << argv[0] << " filename" << endl; 
      return 1; 
   }

   fin.open(argv[1]); 

   if (!fin.is_open()) {
      cout << "Error opening " << argv[1] << endl; 
      return 1; 
   }

   double userArray[ARR_CAP]; 
   double input;  
   int i = 0;
   while (fin >> input && i < ARR_CAP) {
         userArray[i] = input; 
         ++i;
   }

   fin.close(); 

   cout << "Mean: " << mean(userArray, i) << endl << endl;  

   cout << "Enter index of value to be removed (0 to " << i - 1 << ") :" << endl << endl; 
   cin >> removeIndex; 

   cout << "Before removing value: "; 
   display(userArray, i); 
   remove(userArray, i, removeIndex); 

   cout << endl << endl; 

   cout << "After removing value: ";
   
   display(userArray, i); 
   cout << endl << endl; 
   cout << "Mean: " << mean(userArray, i); 
   
	return 0;
}