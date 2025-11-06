#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
   
   string inputFile;
   string outputFile; 
   
   // Assign to inputFile value of 2nd command line argument
   // Assign to outputFile value of 3rd command line argument
   inputFile = argv[1]; 
   outputFile = argv[2];

   if (argc != 3) {
      cout << "Usage: myprog.exe inputFileName outputFileName" << endl;
      return 1;   
   }
   // Create input stream and open input csv file.
   ifstream fin; 

   fin.open(inputFile); 
   // Verify file opened correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if (!fin.is_open()) {
      cout << "Error opening " << inputFile << endl; 
      return 1; 
   }
   // Read in integers from input file to vector. 
   int num; 
   vector<int> v; 

   while (fin >> num) {
      v.push_back(num);
      fin.ignore(); 
   }
   // Close input stream.
   fin.close(); 
   // Get integer average of all values read in.
   int total = 0; 
   int cnt = 0; 
   int avg; 

   for (unsigned int i = 0; i < v.size(); ++i) {
      total += v.at(i);
      ++cnt; 
   }

   avg = total / cnt; 
   // Convert each value within vector to be the difference between the original value and the average.
   for (unsigned int i = 0; i < v.size(); ++i) {
      v.at(i) = v.at(i) - avg; 
   }
   // Create output stream and open/create output csv file.
   ofstream fout; 

   fout.open(outputFile); 
   // Verify file opened or was created correctly.
   // Output error message and return 1 if file stream did not open correctly.
   if (!fout.is_open()) {
      cout << "Error opening " << outputFile << endl; 
      return 1; 
   }
   // Write converted values into ouptut csv file, each integer separated by a comma.
   for (unsigned int i = 0; i < v.size() - 1; ++i) {
      fout << v.at(i) << ","; 
   }

   fout << v.back() << endl; 
   // Close output stream.
   fout.close(); 

   return 0;
}