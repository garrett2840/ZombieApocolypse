#include "district.h"

District::District(int population, std::string name, bool patientZero, bool medicalHill) : name(name) {
    for (int i = 0; i < population; i++) {
        if(i == 0 && patientZero == true) {
            this->population.push_back(new Zombie());
            updateStats(this->population[i]);
        } else if (i < 5 && medicalHill == true) {
            this->population.push_back(new Doctor());
            updateStats(this->population[i]);
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

void District::addDenizen(Denizen* den) {
    population.push_back(den);
    updateStats(den);
}

void District::update() {
    int randIndex = rand() % population.size();
    for (int i = 0; i < population.size(); i++) {
        randIndex = rand() % population.size();
        updateStats(population[randIndex], false);
        population[i]->interact(population[randIndex]);
        updateStats(population[randIndex]);
        updateStats(population[i], false);
        population[randIndex]->interact(population[i]);
        updateStats(population[i]);
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