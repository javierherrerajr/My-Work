#include <iostream>
#include <algorithm>

using namespace std;

// Rational Class declaration
class Rational {
   private:
      int numerator;
      int denominator; 
   public:
      Rational();
      explicit Rational(int num); 
      Rational(int num, int den); 
      Rational add(const Rational &data) const; 
      Rational subtract(const Rational &data) const; 
      Rational multiply(const Rational &data) const; 
      Rational divide(const Rational &data) const;
      void simplify();
      void display() const;
   private:
      int gcd(int top, int bottom) const;
};

// Implement Rational class member functions here
Rational::Rational() {
   numerator = 0; 
   denominator = 1; 
}

Rational::Rational(int num) {
   numerator = num;  
   denominator = 1; 
}

Rational::Rational(int num, int den) {
   numerator = num; 
   denominator = den; 
}

Rational Rational::add(const Rational &data)const {
   Rational sum; 

   sum.numerator = (this->numerator * data.denominator) + (this->denominator * data.numerator); 
   sum.denominator = this->denominator * data.denominator; 

   return sum; 
}

Rational Rational::subtract(const Rational &data)const {
   Rational difference; 

   difference.numerator = (this->numerator * data.denominator) - (this->denominator * data.numerator); 
   difference.denominator = this->denominator * data.denominator; 

   return difference; 
}

Rational Rational::multiply(const Rational &data)const {
   Rational product; 

   product.numerator = this->numerator * data.numerator; 
   product.denominator = this->denominator * data.denominator; 

   return product; 
}

Rational Rational::divide(const Rational &data)const {
   Rational quotient; 

   quotient.numerator = this->numerator * data.denominator; 
   quotient.denominator = this->denominator * data.numerator; 

   return quotient; 
}

int Rational::gcd(int top, int bottom)const {
   return __gcd(top, bottom);
}

void Rational::simplify() { 
   int greatest; 
   greatest = gcd(numerator, denominator);
   numerator = numerator / greatest; 
   denominator = denominator / greatest; 
}

void Rational::display()const {
   cout << numerator << " / " << denominator;
}

// Do not change any of the code below this line!!

Rational getRational();
void displayResult(const string &, const Rational &, const Rational&, const Rational&);

int main() {
   Rational A, B, result;
   char choice;
   
   cout << "Enter Rational A:" << endl;
   A = getRational();
   cout << endl;
   
   cout << "Enter Rational B:" << endl;
   B = getRational();
   cout << endl;
   
   cout << "Enter Operation:" << endl
      << "a - Addition (A + B)" << endl
      << "s - Subtraction (A - B)" << endl
      << "m - Multiplication (A * B)" << endl
      << "d - Division (A / B)" << endl
      << "y - Simplify A" << endl;
   cin >> choice;
   cout << endl;
   
   if (choice == 'a') {
      result = A.add(B);
      displayResult("+", A, B, result);
   } else if (choice == 's') {
      result = A.subtract(B);
      displayResult("-", A, B, result);
   } else if (choice == 'm') {
      result = A.multiply(B);
      displayResult("*", A, B, result);
   } else if (choice == 'd') {
      result = A.divide(B);
      displayResult("/", A, B, result);
   } else if (choice == 'y') {
      A.simplify();
      A.display();
   } else {
      cout << "Unknown Operation";
   }
   cout << endl;
   
   return 0;
}


Rational getRational() {
   int choice;
   int numer, denom;
   
   cout << "Which Rational constructor? (Enter 2, 1, or 0)" << endl
      << "2 - 2 parameters (numerator & denominator)" << endl
      << "1 - 1 parameter (numerator)" << endl
      << "0 - 0 parameters (default)" << endl;
   cin >> choice;
   cout << endl;
   
   if (choice == 2) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      cout << "denominator? ";
      cin >> denom;
      cout << endl;
      return Rational(numer, denom);
   } else if (choice == 1) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      return Rational(numer);
   } else {
      return Rational();
   }
}

void displayResult(const string &op, const Rational &lhs, const Rational&rhs, const Rational &result) {
   cout << "(";
   lhs.display();
   cout << ") " << op << " (";
   rhs.display();
   cout << ") = (";
   result.display();
   cout << ")";
}

