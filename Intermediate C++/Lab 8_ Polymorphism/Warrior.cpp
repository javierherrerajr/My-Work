#include <string>
#include <iostream>
#include "Warrior.h"

using namespace std;

Warrior::Warrior(const string & n, double h, double aS, string a)
    :Character(WARRIOR, n, h, aS), allegiance(a){}

const string & Warrior::getAllegiance() const{
    return allegiance;
}

void Warrior::attack(Character & c) {
    if (c.getType() == WARRIOR){
        Warrior &challenger = dynamic_cast<Warrior &>(c);
        if (allegiance == challenger.getAllegiance()){
            cout << "Warrior " << name << " does not attack Warrior " << challenger.getName() 
                 << "." << endl << "They share an allegiance with " << allegiance << "." << endl;
        }
        else{
            double d = (health / MAX_HEALTH) * attackStrength;
            challenger.damage(d);
            cout << "Warrior " << name << " attacks " << c.getName() << " --- SLASH!!" << endl
                 << c.getName() << " takes " << d << " damage." << endl;
        }
    }
    else{ 
        double d = (health / MAX_HEALTH) * attackStrength;
        c.damage(d);
        cout << "Warrior " << name << " attacks " << c.getName() << " --- SLASH!!" << endl
             << c.getName() << " takes " << d << " damage." << endl;
    }
}