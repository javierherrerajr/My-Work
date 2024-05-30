#include <iostream>
#include <string>
#include <vector>
using namespace std;

void DisplayMenu() {
   cout << "Menu options:" << endl; 
   cout << "1. Display All Seats Status:" << endl; 
   cout << "2. Total Number of Available Seats:" << endl; 
   cout << "3. Display Available Seats: " << endl; 
   cout << "4. Book Seat:" << endl; 
   cout << "5. Cancel Seat:" << endl; 
   cout << "6. Change Seat:" << endl; 
   cout << "7. Quit:" << endl << endl; 
   cout << "Please select an option: " << endl << endl; 
}

void DisplayAllSeatsStatus(const vector<string> &seats, const vector<bool> &availability) {
   cout << "Seat\tStatus" << endl; 
   
   for (unsigned int i = 0; i < seats.size(); ++i) {
      cout << seats.at(i) << "\t" << availability.at(i) << endl; 
   }
   
   cout << endl;
}

void DisplayAvailableSeats(const vector<string> &seats, const vector<bool> &availability) {
   cout << "Available seats:" << endl; 
   for (unsigned int i = 0; i < seats.size(); ++i) {
      if (availability.at(i) != true) {
         cout << seats.at(i) << endl; 
      }
   }
   
   cout << endl; 
}

int TotalNumberOfAvailableSeats(const vector<bool> &availability) {
   int cnt = 0; 
   
   for (unsigned int i = 0; i < availability.size(); ++i) {
      if (availability.at(i) == false) {
         ++cnt; 
      }
   }
   
   return cnt; 
}

void BookSeat(const string &choice1, const vector<string> &seats, vector<bool> &availability) {
   int f; 
   string choice2; 
   
   for (unsigned int i = 0; i < seats.size(); ++i) {
            if (seats.at(i) == choice1) {
               f = i;
            }
         }
         while (availability.at(f) == true) {
            cout << "That seat is already taken." << endl; 
            cout << "Enter seat to book: "; 
            cin >> choice2; 
            for (unsigned int i = 0; i < seats.size(); ++i) {
            if (seats.at(i) == choice2) {
               f = i;
            }
         }
            cout << endl << endl; 
         }
         availability.at(f) = true;

   cout << "Seat\tStatus" << endl; 
   for (unsigned int i = 0; i < seats.size(); ++i) {
      cout << seats.at(i) << "\t" << availability.at(i) << endl; 
   }
   
   cout << endl; 
}

void CancelSeat (const string &choice1, const vector<string> &seats, vector<bool> &availability) {
   int f; 
   
   for (unsigned int i = 0; i < seats.size(); ++i) {
            if (seats.at(i) == choice1) {
               f = i;
            }
         }
         availability.at(f) = false;

   cout << "Seat\tStatus" << endl; 
   
   for (unsigned int i = 0; i < seats.size(); ++i) {
      cout << seats.at(i) << "\t" << availability.at(i) << endl; 
   }
   
   cout << endl; 
}

void ChangeSeat(const string &choice1, const string &choice2, const vector<string> &seats, vector<bool> &availability) {
   int f; 
   int n; 
   
   for (unsigned int i = 0; i < seats.size(); ++i) {
            if (seats.at(i) == choice1) {
               f = i;
            }
         }
      
         availability.at(f) = false;
   
   for (unsigned int i = 0; i < seats.size(); ++i) {
            if (seats.at(i) == choice2) {
               n = i;
            }
         }
         availability.at(n) = true;

   cout << "Seat\tStatus" << endl; 
   
   for (unsigned int i = 0; i < seats.size(); ++i) {
      cout << seats.at(i) << "\t" << availability.at(i) << endl; 
   }
   
   cout << endl;
}

int main() {
   vector<string> seatList; 
   vector<bool> seatStatus;
   int seatNumber;
   int userOption; 
   char seatLetter;
   string seatNumberConverter;  
   string seats; 
   string seatChoice; 
   string seatChoice2; 
   
   for (seatNumber = 1; seatNumber <= 5; ++seatNumber) {
      seatLetter = 'A'; 
      for (unsigned int i = 0; i < 5; ++i) {
         seatNumberConverter = to_string(seatNumber); 
         seats = seatNumberConverter + seatLetter; 
         seatList.push_back(seats); 
         ++seatLetter; 
      }
   }
   
   seatStatus.resize(seatList.size()); 
   
   for (unsigned int i = 0; i < seatList.size(); ++i) {
      seatStatus.at(i) = false; 
   }
   
   DisplayMenu(); 
   
   cin >> userOption;  
   
   while (userOption != 7) {
      if (userOption == 1) {
         DisplayAllSeatsStatus (seatList, seatStatus); 
      }
      
      else if (userOption == 2) {
         cout << "Number of available seats: " << TotalNumberOfAvailableSeats (seatStatus) << endl << endl; 
      }
      
      else if (userOption == 3) {
         DisplayAvailableSeats (seatList, seatStatus);
      }
      
      else if (userOption == 4) {
         cout << "Enter seat to book: ";
         cin >> seatChoice; 
         cout << endl << endl; 
         BookSeat (seatChoice, seatList, seatStatus); 
      }
      
      else if (userOption == 5) {
         cout << "Enter seat to cancel: "; 
         cin >> seatChoice; 
         cout << endl << endl;  
         CancelSeat (seatChoice, seatList, seatStatus);
      }
      
      else if (userOption == 6) {
         cout << "Enter seat to cancel: "; 
         cin >> seatChoice; 
         cout << endl << endl; 
          
         cout << "Enter seat to book: "; 
         cin >> seatChoice2; 
         cout << endl << endl;
         
         ChangeSeat (seatChoice, seatChoice2, seatList, seatStatus);
      }
      
      DisplayMenu(); 
      
      cin >> userOption; 
   }
   
   return 0;
}