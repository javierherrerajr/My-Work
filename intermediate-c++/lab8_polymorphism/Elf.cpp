#include <string>
#include <iostream>
#include "Elf.h"

using namespace std;

Elf::Elf(const string & n, double h, double aS, string f)
    :Character(ELF, n, h, aS), family(f){}

const string & Elf::getFamily() const{
    return family;
}

void Elf::attack(Character & c) {
    if (c.getType() == ELF){
        Elf &challenger = dynamic_cast<Elf &>(c);
        if (family == challenger.getFamily()){
            cout << "Elf " << name << " does not attack Elf " << challenger.getName() << "." << endl
                 << "They are both members of the " << family << " family." << endl;
        }
        else{
            double d = (health / MAX_HEALTH) * attackStrength;
            challenger.damage(d);
            cout << "Elf " << name << " shoots an arrow at " << c.getName() << " --- TWANG!!" << endl
                 << c.getName() << " takes " << d << " damage." << endl;
        }
    }
    else{
        double d = (health / MAX_HEALTH) * attackStrength;
        c.damage(d);
        cout << "Elf " << name << " shoots an arrow at " << c.getName() << " --- TWANG!!" << endl
             << c.getName() << " takes " << d << " damage." << endl;
    }
}