#include "district.h"

District::District(int population, std::string name, bool patientZero, bool medicalHill) : name(name) {
    // Adds denizens to the district
    for (int i = 0; i < population; i++) {
        // If patientZero arises from this district
        if(i == 1 && patientZero == true) {
            // Add a zombie!
            this->population.push_back(new Zombie());
            updateStats(this->population[i]);
        // If the district is Medical Hill
        } else if (i < 9 && medicalHill == true) {
            // Add 9 Doctors!
            this->population.push_back(new Doctor());
            updateStats(this->population[i]);
        // Fill the remaining spots with ignorant
        } else {
            this->population.push_back(new Ignorant());
            updateStats(this->population[i]);
        }
    }
}

std::string District::getName() { return name; }

std::string District::getStats() {
    std::string temp = name + ":\n";
    temp += "\tIgnorant: " + std::to_string(stats["Ignorant"]) + "\n";
    temp += "\tAlarmed: " + std::to_string(stats["Alarmed"]) + "\n";
    temp += "\tZombie: " + std::to_string(stats["Zombie"]) + "\n";
    temp += "\tDoctor: " + std::to_string(stats["Doctor"]) + "\n";
    return temp;
}

void District::update() {
    // Generates a random index
    int randIndex = rand() % population.size();
    // Iterates through the entire district population
    for (int i = 0; i < population.size(); i++) {
        // Updates the random index
        randIndex = rand() % population.size();
        // Removes the denizen at the random index from the stat pool
        updateStats(population[randIndex], false);
        // Denizen at index i interacts with the denizen at the random index 
        population[i]->interact(population[randIndex]);
        // Adds the denizen at the random index back to the stat pool
        updateStats(population[randIndex]);
    }
}

void District::updateStats(Denizen* den, bool add) {
    // Checks if denizen is Ignorant
    if (typeid(*den) == typeid(Ignorant)) {
        // Adds denizen to stats if add is true, if false, removes denizen from stats
        if (add == true) {
            stats["Ignorant"]++;
        } else {
            stats["Ignorant"]--;
        }
    }
    // Checks if denizen is Alarmed
    if (typeid(*den) == typeid(Alarmed)) {
        // Adds denizen to stats if add is true, if false, removes denizen from stats
        if (add == true) {
            stats["Alarmed"]++;
        } else {
            stats["Alarmed"]--;
        }
    }
    // Checks if denizen is a Zombie
    if (typeid(*den) == typeid(Zombie)) {
        // Adds denizen to stats if add is true, if false, removes denizen from stats
        if (add == true) {
            stats["Zombie"]++;
        } else {
            stats["Zombie"]--;
        }
    }
    // Checks if denizen is a Doctor
    if (typeid(*den) == typeid(Doctor)) {
        // Adds denizen to stats if add is true, if false, removes denizen from stats
        if (add == true) {
            stats["Doctor"]++;
        } else {
            stats["Doctor"]--;
        }
    }
    
}