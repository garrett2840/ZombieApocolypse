#include <iostream>
#include "city.h"

int main() {
    srand(time(NULL));
    City simulation(2000, "Simville", "names.txt");
    simulation.run();
}