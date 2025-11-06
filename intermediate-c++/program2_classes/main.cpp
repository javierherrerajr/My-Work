#include <iostream>
#include <string>

using namespace std;

class Date {
 private:
   unsigned day;
   unsigned month;
   string monthName;
   unsigned year;

 public:
   // creates the date January 1st, 2000.
   Date();


   /* parameterized constructor: month number, day, year 
       - e.g. (3, 1, 2010) will construct the date March 1st, 2010

       If any of the arguments are invalid (e.g. 15 for month or 32 for day)
       then the constructor will construct instead a valid Date as close
       as possible to the arguments provided - e.g. in above example,
       Date(15, 32, 2010), the Date would be corrected to Dec 31st, 2010.
       In case of such invalid input, the constructor will issue a console error message: 

       Invalid date values: Date corrected to 12/31/2010.
       (with a newline at the end).
   */
   Date(unsigned m, unsigned d, unsigned y);


   /* parameterized constructor: month name, day, year
      - e.g. (December, 15, 2012) will construct the date December 15th, 2012

       If the constructor is unable to recognize the string argument as a valid month name,
       then it will issue a console error message: 

       Invalid month name: the Date was set to 1/1/2000.
       (with a newline at the end).
 
       If the day argument is invalid for the given month (but the month name was valid),
       then the constructor will handle this error in the same manner as the other
       parameterized constructor. 

       This constructor will recognize both "december" and "December"
       as month name.
   */
   Date(const string &mn, unsigned d, unsigned y);


   /* Outputs to the console (cout) a Date exactly in the format "3/15/2012". 
      Does not output a newline at the end.
   */
   void printNumeric() const;


   /* Outputs to the console (cout) a Date exactly in the format "March 15, 2012".
      The first letter of the month name is upper case, and the month name is
      printed in full - January, not Jan, jan, or january. 
      Does not output a newline at the end.
   */
   void printAlpha() const;

 private:

   /* Returns true if the year passed in is a leap year, otherwise returns false.
   */
   bool isLeap(unsigned y) const {
      bool isLeapYear = false; 

      if (y % 4 == 0) {
         isLeapYear = true;  
      }

      if (y % 100 == 0) {
         isLeapYear = false;  
      }

      if (y % 400 == 0) {
         isLeapYear = true; 
      }

      return isLeapYear; 
   }

   /* Returns number of days allowed in a given month
      -  e.g. daysPerMonth(9, 2000) returns 30.
      Calculates February's days for leap and non-leap years,
      thus, the reason year is also a parameter.
   */
   unsigned daysPerMonth(unsigned m, unsigned y) const {
      if (m == 2) {
         if (isLeap(y)) {
            return 29; 
         }

         else {
            return 28; 
         }
      }

      else if ((m == 1) || (m == 3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12)) {
         return 31; 
      }

      else {
         return 30; 
      }
   }
      
   /* Returns the name of a given month
      - e.g. name(12) returns the string "December"
   */
   string name(unsigned m) const {
      if (m == 1) {
         return "January"; 
      }

      if (m == 2) {
         return "February";
      }

      if (m == 3) {
         return "March"; 
      }

      if (m == 4) {
         return "April"; 
      }

      if (m == 5) {
         return "May"; 
      }

      if (m == 6) {
         return "June"; 
      }

      if (m == 7) {
         return "July"; 
      }

      if (m == 8) {
         return "August"; 
      }

      if (m == 9) {
         return "September"; 
      }

      if (m == 10) {
         return "October"; 
      }

      if (m == 11) {
         return "November";
      }

      if (m == 12) {
         return "December"; 
      }
   }

   /* Returns the number of a given named month
      - e.g. number("March") returns 3
   */
   unsigned number(const string &mn) const {
      if (mn == "January" || mn == "january") {
         return 1; 
      }

      if (mn == "February" || mn == "february") {
         return 2; 
      }

      if (mn == "March" || mn == "march") {
         return 3; 
      }

      if (mn == "April" || mn == "april") {
         return 4; 
      }

      if (mn == "May" || mn == "may") {
         return 5; 
      }

      if (mn == "June" || mn == "june") {
         return 6; 
      }

      if (mn == "July" || mn == "july") {
         return 7; 
      }

      if (mn == "August" || mn == "august") {
         return 8; 
      }

      if (mn == "September" || mn == "september") {
         return 9;
      }

      if (mn == "October" || mn == "october") {
         return 10; 
      }

      if (mn == "November" || "november") {
         return 11; 
      }

      if (mn == "December" || mn == "december") {
         return 12; 
      }
   }
};


// Implement the Date member functions here
Date::Date() {
   day = 1;
   month = 1;
   monthName = "January"; 
   year = 2000; 
}

Date::Date(unsigned m, unsigned d, unsigned y) {
   int cnt = 0; 
   month = m; 
   day = d; 
   year = y;  
   
   if (m < 1) {
         m = 1;
         month = 1; 
         monthName = "January";  
         ++cnt; 
   }

   else if (m > 12) {
         m = 12; 
         month = 12; 
         monthName = "December"; 
         ++cnt; 
   }

   if (d < 1) {
         d = 1;
         day = 1; 
         ++cnt; 
   }

   else if (d > 31) {
         d = 31;
         day = 31;  
         ++cnt; 
   }

   if (m == 2) {
      monthName = "February";
      if (isLeap(y)) {
         if (d > daysPerMonth(m, y)) {
            d = daysPerMonth(m, y); 
            day = 29; 
            ++cnt; 
         }
      }

      else {
         if (d > daysPerMonth(m, y)) {
            d = daysPerMonth(m, y); 
            day = 28; 
            ++cnt; 
         }
      }
   }

   else if ((m == 4) || (m == 6) || (m == 9) || (m == 11)) {
      if (d > daysPerMonth(m, y)) {
         d = daysPerMonth(m, y);
         day = 30;  
         ++cnt; 
      }

      if (m == 4) {
         monthName = "April"; 
      }
      
      else if (m == 6) {
         monthName = "June"; 
      }

      else if (m == 9) {
         monthName = "September";
      }

      else {
         monthName = "November"; 
      }
   }

   else {
      if (m == 1) {
         monthName = "January"; 
      }

      else if (m == 3) {
         monthName = "March";
      }

      else if (m == 4) {
         monthName = "May"; 
      }

      else if (m == 6) {
         monthName = "July"; 
      }

      else if (m == 8) {
         monthName = "August";
      }

      else if (m == 10) {
         monthName = "October";
      }

      else {
         monthName = "December"; 
      }
   }

   if (cnt > 0) {
      cout << "Invalid date values: Date corrected to " << m << "/" << d << "/" << y << "." << endl; 
   }
}

Date::Date(const string &mn, unsigned d, unsigned y) {
   int cnt = 0;  

   monthName = mn; 
   day = d; 
   year = y;

   if (d < 1) {
      d = 1;
      day = 1;  
      ++cnt; 
   } 

   if (!((mn == "January") || (mn == "january") || (mn == "February") || (mn == "february") || (mn == "March") || (mn == "march") || (mn == "April") || (mn == "april") || (mn == "May") || (mn == "may") || (mn == "June") || (mn == "june") || (mn == "July") || (mn == "july") || (mn == "August") || (mn == "august") || (mn == "September") || (mn == "september") || (mn == "October") || (mn == "october") || (mn == "November") || (mn == "november") || (mn == "December") || (mn == "december"))) {
      month = 1; 
      day = 1; 
      year = 2000; 
      monthName = "January";
      cout << "Invalid month name: the Date was set to 1/1/2000." << endl; 
   }

   else if (mn == "January" || mn == "january") {
      monthName = "January"; 
      month = 1; 
      if (day > 31) {
         d = 31; 
         day = 31; 
         ++cnt; 
      }
   }

   else if (mn == "February" || mn == "february") {
      monthName = "February"; 
      month = 2; 
      if (isLeap(y)) {
         if (d > 29) {
            d = 29; 
            day = 29; 
            ++cnt; 
         }
      }

      else { 
         if (d > 28) {
         d = 28;
         day = 28;  
         ++cnt;
         } 
      }
   }

   else if (mn == "March" || mn == "march") {
      monthName = "March"; 
      month = 3; 
      if (d > 31) {
         d = 31; 
         day = 31; 
         ++cnt; 
      }
   }

   else if (mn == "April" || mn == "april") {
      monthName = "April"; 
      month = 4; 
      if (d > 30) {
         d = 30; 
         day = 30; 
         ++cnt; 
      }
   }

   else if (mn == "May" || mn == "may") {
      monthName = "May"; 
      month = 5; 
      if (d > 31) {
         d = 31; 
         day = 31; 
         ++cnt; 
      } 
   }

   else if (mn == "June" || mn == "june") {
      monthName = "June"; 
      month = 6; 
      if (d > 30) {
         d = 30; 
         day = 30; 
         ++cnt; 
      } 
   }

   else if (mn == "July" || mn == "july") {
      monthName = "July";
      month = 7; 
      if (d > 31) {
         d = 31;
         day = 31;  
         ++cnt; 
      } 
   }

   else if (mn == "August" || mn == "august") {
      monthName = "August";
      month = 8; 
      if (d > 31) {
         d = 31; 
         day = 31; 
         ++cnt; 
      } 
   }

   else if (mn == "September" || mn == "september") {
      monthName = "September"; 
      month = 9; 
      if (d > 30) {
         d = 30; 
         day = 30; 
         ++cnt; 
      }
   }

   else if (mn == "October" || mn == "october") {
      monthName = "October"; 
      month = 10; 
      if (d > 31) {
         d = 31;
         day = 31;  
         ++cnt; 
      } 
   }

   else if (mn == "November" || "november") {
      monthName = "November"; 
      month = 11; 
      if (d > 30) {
         d = 30; 
         day = 30; 
         ++cnt; 
      }
   }

   else if (mn == "December" || mn == "december") {
      monthName = "December"; 
      month = 12; 
      if (d > 31) {
         d = 31;
         day = 31;  
         ++cnt; 
      }
   }

   if (cnt > 0) {
      cout << "Invalid date values: Date corrected to " << month << "/" << d << "/" << y << "." << endl; 
   }
}

void Date::printNumeric()const {
   cout << month << "/" << day << "/" << year; 
}

void Date::printAlpha()const {
   cout << monthName << " " << day << ", " << year; 
}
// Don't change the code below this line.
// You may comment them out if you want to build your own test harness
// while in develope mode, but you will need these to pass tets in submit mode.

Date getDate();

int main() {
   
   Date testDate;
   testDate = getDate();
   cout << endl;
   cout << "Numeric: ";
   testDate.printNumeric();
   cout << endl;
   cout << "Alpha:   ";
   testDate.printAlpha();
   cout << endl;
   
   return 0;
}

Date getDate() {
   int choice;
   unsigned monthNumber, day, year;
   string monthName;

   cout << "Which Date constructor? (Enter 1, 2, or 3)" << endl
      << "1 - Month Number" << endl
      << "2 - Month Name" << endl
      << "3 - default" << endl;
   cin >> choice;
   cout << endl;

   if (choice == 1) {
      cout << "month number? ";
      cin >> monthNumber;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthNumber, day, year);
   } else if (choice == 2) {
      cout << "month name? ";
      cin >> monthName;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthName, day, year);
   } else {
      return Date();
   }
}
