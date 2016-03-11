#include "Lord.h"
#include<iostream>
#include<vector>

Lord::Lord()
{
    //ctor
}

Lord::Lord (std::string nam,std::string ter, int hon, int pio, int gre, int adv, int lav)
    :name (nam),
    territory (ter),
    honorable (hon),
    pious (pio),
    gregarious (gre),
    adventurous (adv),
    lavish (lav)
{}

Lord::~Lord()
{
    //dtor
}



void Lord::showDetails() {
    std::cout << name << " is lord of " << territory;
    std::cout << "\nHonorable: " << honorable;
    std::cout << "\nPious: " << pious;
    std::cout << "\nGregarious: " << gregarious;
    std::cout << "\nAdventurous: " << adventurous;
    std::cout << "\nLavish: " << lavish;
}
