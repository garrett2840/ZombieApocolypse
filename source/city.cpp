#include "city.h"

City::City(int population, std::string name) : name(name) {
    districts.push_back(District(population * 0.10, "Medical Hill", false, true));
    districts.push_back(District(population * 0.15, "University District", true));
    districts.push_back(District(population * 0.45, "Suburbs"));
    districts.push_back(District(population * 0.30, "Downtown"));
    updateStats();
    hour--;
    std::cout << getStats() << std::endl;
}

std::string City::getStats() {
    std::string temp = "";
    temp += name + " | Hour: " + std::to_string(hour) + "\n";
    temp += "Total City | Ignorant: " + std::to_string(stats["Ignorant"]);
    temp += " | Alarmed: " + std::to_string(stats["Alarmed"]);
    temp += " | Zombie: " + std::to_string(stats["Zombie"]);
    temp += " | Doctor: " + std::to_string(stats["Doctor"]) + "\n";
    for (auto itr = districts.begin(); itr != districts.end(); itr++) {
        temp += itr->getName() + " | Ignorant: " + std::to_string(itr->stats["Ignorant"]);
        temp += " | Alarmed: " + std::to_string(itr->stats["Alarmed"]);
        temp += " | Zombie: " + std::to_string(itr->stats["Zombie"]);
        temp += " | Doctor: " + std::to_string(itr->stats["Doctor"]) + "\n";
    }
    return temp;
}

void City::run(int days) {
    for (int i = 0; i < days * 24; i++) {
        for (auto itr = districts.begin()++; itr != districts.end(); itr++) {
            itr->update();
        }
        migrate();
        updateStats();
        std::cout << getStats() << std::endl;
    }
}

void City::migrate() {
    auto nxtDist = districts.begin();
    // Iterates through all districts
    for (auto itr = districts.begin(); itr != districts.end(); ++itr) {
        // Iterates through all denizens in current district
        for (int i = 0; i < itr->population.size(); i++) {
            // Checks if current denizen would like to move
            if (itr->population[i]->move() == true) {
                Denizen* temp = itr->population[i];
                // delete itr->population[i]; // Free the memory associated with the denizen
                itr->population[i] = NULL;
                itr->updateStats(temp, false);
                if (nxtDist == districts.end()) {
                    // If nxtDist is at the end of the vector, reset it to the beginning
                    nxtDist = districts.begin();
                }
                nxtDist->population.push_back(temp);
                nxtDist->updateStats(temp);
                ++nxtDist;
            }
            itr->population.shrink_to_fit();
        }
        // Remove the denizens that have moved from the district
        itr->population.erase(std::remove(itr->population.begin(), itr->population.end(), nullptr), itr->population.end());
    }
}

void City::updateStats() {
    std::string type[4] = { "Ignorant", "Alarmed", "Zombie", "Doctor" };
    for (int i = 0; i < 4; i++) {
        stats[type[i]] = 0;
    }
    for (auto itr = districts.begin(); itr != districts.end(); itr++) {
        for (int i = 0; i < 4; i++) {
            stats[type[i]] += itr->stats[type[i]];
        }
    }
    hour++;
}

std::vector<std::string> City::feedNames(std::string directory) {}