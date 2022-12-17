///////////////////////////////////////////////////////////////////////
//  Zombie Apocalypse Simulation!                                    //
//  Developed by Jacob Ojennus, Zach Marble, and Garrett Daviscourt  //
//  For CS-274-1                                                     //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include "city.h"

int main() {
    // Seeds random
    srand(time(NULL));
    // Creates an instance of the city class
    City simulation(2000, "Simville", "names.txt");
    // Commences the simulation!!
    simulation.run();
}