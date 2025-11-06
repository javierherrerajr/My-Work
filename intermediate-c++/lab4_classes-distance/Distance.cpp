#include <iostream>
using namespace std; 

#include "Distance.h"

Distance::Distance() {
    feet = 0; 
    inches = 0.0;
}

Distance::Distance(unsigned ft, double in) {
    feet = ft; 
    inches = in; 

    init(); 
}

Distance::Distance(double in) {
    feet = 0; 
    inches = in; 

    init(); 
}

unsigned Distance::getFeet()const {
    return feet; 
}

double Distance::getInches()const {
    return inches; 
}

double Distance::distanceInInches()const {
    return (feet * 12) + inches; 
}

double Distance::distanceInFeet()const {
    return feet + (inches / 12); 
}

double Distance::distanceInMeters()const {
    return ((feet * 12) + inches) * 0.0254; 
}

Distance Distance::operator+(const Distance &rhs)const {
    Distance newDistance; 

    newDistance.feet = feet + rhs.feet; 
    newDistance.inches = inches + rhs.inches; 
    newDistance.init(); 

    return newDistance; 
}

Distance Distance::operator-(const Distance &rhs)const {
    Distance newDistance; 

    if (feet > rhs.feet) {
        newDistance.feet = feet - rhs.feet; 
        
        if (inches > rhs.inches) {
            newDistance.inches = inches - rhs.inches; 
        }

        else {
            --newDistance.feet; 
            newDistance.inches = (inches + 12) - rhs.inches; 
        }
    }

    else {
        newDistance.feet = rhs.feet - feet; 

        if (rhs.inches > inches) {
            newDistance.inches = rhs.inches - inches; 
        }

        else {
            --newDistance.feet;
            newDistance.inches = (rhs.inches + 12) - inches; 
        }
    }

    return newDistance; 
}

ostream & operator<<(ostream &out, const Distance &rhs) {
    out << rhs.feet << "' " << rhs.inches << "\"";

    return out; 
}

void Distance::init() {
    if (inches < 0) {
        inches *= -1; 
    }

    while (inches >= 12) {
        ++feet; 
        inches -= 12; 
    }
}