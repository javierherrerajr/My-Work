#include <iostream>
#include <fstream>
using namespace std; 

double mean(const double array[], int arraySize){
   double mean = 0.0; 
   double sum = 0.0; 

   for (int i = 0; i < arraySize; ++i) {
      sum += array[i]; 
   }

   mean = sum / arraySize; 

   return mean; 
}

void remove(double array[], int &arraySize, int index){
   if (index == arraySize - 1) {
      --arraySize; 
   }

   else {
      for (int i = index; i + 1 < arraySize; ++i) {
         array[i] = array[i + 1]; 
      }  

      --arraySize;
   }
}

void display(const double array[], int arraySize){
   for (int i = 0; i + 1 < arraySize; ++i) {
      cout << array[i] << ", "; 
   }

   cout << array[arraySize - 1];
}


const int ARR_CAP = 100;

int main(int argc, char *argv[]) {
   ifstream fin; 
   double userInput;
   int i = 0; 

   if (argc != 2) {
      cout << "USAGE: " << argv[0] << " filename" << endl; 
      return 1; 
   }
   
   fin.open(argv[1]); 

   if (!fin.is_open()) {
      cout << "Error opening " << argv[1] << endl; 
      return 1; 
   }

   double array[ARR_CAP]; 
   
   while (fin >> userInput && i < ARR_CAP) {
      array[i] = userInput; 
      ++i;     
   }

   fin.close(); 
   
   int arrayS; 
   arrayS = i; 

   cout << "Mean: " << mean(array, arrayS) << endl; 
   cout << endl;  
   cout << "Enter index of value to be removed (0 to " << arrayS - 1 << ") :" << endl;
   cout << endl; 
   cout << "Before removing value: ";  

   display(array, arrayS); 

   cout << endl << endl; 
   
   int userIndex; 
   
   cin >> userIndex; 

   remove(array, arrayS, userIndex);

   cout << "After removing value: "; 
   
   display(array, arrayS); 

   cout << endl << endl; 
   cout << "Mean: " << mean(array, arrayS); 
   
	return 0;
}