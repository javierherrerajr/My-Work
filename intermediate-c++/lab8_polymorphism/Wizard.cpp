#include <string>
#include <iostream>
#include "Wizard.h"

using namespace std;

Wizard::Wizard(const string & n, double h, double aS, int r)
    :Character(WIZARD, n, h, aS), rank(r){}

int Wizard::getRank() const{
    return rank;
}

void Wizard::attack(Character & c) {
    if (c.getType() == WIZARD){
        Wizard &challenger = dynamic_cast<Wizard &>(c);
        double d = (static_cast<double>(rank)/static_cast<double>(challenger.getRank())) * attackStrength;
        challenger.damage(d);
        cout << "Wizard " << name << " attacks " << c.getName() << " --- POOF!!" << endl
             << c.getName() << " takes " << d << " damage." << endl;
    }
    else {
        c.damage(attackStrength);
        cout << "Wizard " << name << " attacks " << c.getName() << " --- POOF!!" << endl
             << c.getName() << " takes " << attackStrength << " damage." << endl;
    }
}