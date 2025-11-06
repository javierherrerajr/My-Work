#include <string>
#include "Character.h"

using namespace std;

Character::Character(HeroType t, const string & n, double h, double aS){
    type = t;
    name = n;
    if (h <= MAX_HEALTH){
        health = h;
    }
    else{
        health = MAX_HEALTH;
    }
    attackStrength = aS;
}

HeroType Character::getType() const{
    return type;
}

const string & Character::getName() const{
    return name;
}

int Character::getHealth() const{
    return static_cast<int>(health);
}

void Character::damage(double d){
    health -= d;
}

bool Character::isAlive() const{
    bool isAlive = false; 
    if (getHealth() > 0){
        isAlive = true; 
    }

    return isAlive; 
}