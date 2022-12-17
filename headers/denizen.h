#ifndef DENIZEN_H
#define DENIZEN_H

#include <cstdlib>
#include <string>

class Denizen {
protected:
    std::string name; // Holds name
    int infectionProb; // Holds the infection probability
public:
    // Constructor
    Denizen(int infectionProb, std::string name = "Not Assigned") : 
        infectionProb(infectionProb), name(name) {}
    // Destructor
    ~Denizen() {}
    // Getters
    std::string getName() { return name; } // Gets the name of the denizen
    int getInfectionProb() { return infectionProb; } // Gets the infection probability of the denizen
    // Polymorphic Interact Function
    virtual void interact(Denizen* &neighbor) {}
    // Polymorphic Move Function
    virtual bool move() { return false; }
};

// Ignorant Class, child of Denizen
// Has a 50% chance of being infected by a zombie
// Has a 0% chance of moving to another district
// Cannot interact with other denizens
class Ignorant : public Denizen {
public:
    // Constructor
    Ignorant(std::string name = "Not Assigned") : Denizen(20, name) {}
    // Copy Constructor
    Ignorant(Denizen* old) : Denizen(20, old->getName()) {}
    // Destructor
    ~Ignorant() {}
};

// Alarmed Class, child of Denizen
// Has a 25% chance of being infected by a zombie
// Has a 10% chance of moving to another district
// Cannot interact with other denizens
class Alarmed : public Denizen {
public:
    // Constructor
    Alarmed(std::string name = "Not Assigned") : Denizen(10, name) {}
    // Copy Constructor
    Alarmed(Denizen* old) : Denizen(10, old->getName()) {}
    // Destructor
    ~Alarmed() {}
    // Polymorphic Interact Function
    virtual void interact(Denizen* &neighbor) {
        // Checks if neighbor is ignorant
        if (typeid(*neighbor) == typeid(Ignorant)) {
            // Calculate Probability of becoming alarmed
            if ((rand() % 100) < 25) {
                // Create the alarmed version of the neighbor
                Denizen* temp = new Alarmed(neighbor);
                delete neighbor;
                neighbor = temp;
            }
        }
    }
    // Polymorphic Move Function
    virtual bool move() {
        // Calculates the probability of movement
        if ((rand() % 100) < 10) {
            return true;
        }
        return false;
    }
};

// Zombie Class, child class of Denizen
// Has a 0% chance of being infected and various probabilities of infecting other denizens
// Has a 5% chance of moving to another district
// Can interact with any denizen type except other zombies
class Zombie : public Denizen {
public:
    // Constructor
    Zombie(std::string name = "Not Assigned") : Denizen(0, name) {}
    // Copy Constructor
    Zombie(Denizen* old) : Denizen(0, old->getName()) {}
    // Destructor
    ~Zombie() {}
    // Polymorphic Interact Function
    virtual void interact(Denizen* &neighbor) {
        // Checks if neighbor is not a zombie
        if (typeid(*neighbor) != typeid(Zombie)) {
            // Calculate infection probability
            if ((rand() % 100) < neighbor->getInfectionProb()) {
                // Create the zombified version of the neighbor
                Denizen* temp = new Zombie(neighbor);
                delete neighbor;
                neighbor = temp;
            } else if (typeid(*neighbor) == typeid(Ignorant)) {
                // Create the alarmed version of the neighbor
                Denizen* temp = new Alarmed(neighbor);
                delete neighbor;
                neighbor = temp;
            }
        }
    }
    // Polymorphic Move Function
    virtual bool move() {
        // Calculates the probability of movement
        if ((rand() % 100) < 5) {
            return true;
        }
        return false;
    }
};

// Doctor Class, child of Denizen
// Has a 15% chance of being infected and a 40% chance of healing a zombie
// Has a 100% chance of moving to another district
// Can only interact with zombies
class Doctor : public Denizen {
public:
    // Constructor
    Doctor(std::string name = "Not Assigned") : Denizen(8, name) {}
    // Copy Constructor
    Doctor(Denizen* old) : Denizen(8, old->getName()) {}
    // Destructor
    ~Doctor() {}
    // Polymorphic Interact Function
    virtual void interact(Denizen* &neighbor) {
        // Checks if neighbor is a zombie
        if (typeid(*neighbor) == typeid(Zombie)) {
            // Calculate probability of healing
            if ((rand() % 100) < 50) {
                // Create the alarmed version of the neighbor
                Denizen* temp = new Alarmed(neighbor);
                delete neighbor;
                neighbor = temp;
            }
        }
    }
    // Polymorphic Move Function
    virtual bool move() {
        // Calculates the probability of movement
        if ((rand() % 100) < 90) {
            return true;
        }
        return false;
    }
};

#endif