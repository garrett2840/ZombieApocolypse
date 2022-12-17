#include "city.h"

City::City(int population, std::string name, std::string namesDirectory) : name(name) {
    // Populates a vector with all of the denizen names
    std::vector<std::string> names = feedNames(namesDirectory);
    // Adds districts to the list of districts
    districts.push_back(District(population * 0.10, "Medical Hill", false, true));
    districts.push_back(District(population * 0.15, "University District", true));
    districts.push_back(District(population * 0.45, "Suburbs"));
    districts.push_back(District(population * 0.30, "Downtown"));
    // Updates the beginning stats
    updateStats();
    hour--;
    std::cout << getStats() << std::endl;
}

std::string City::getStats() {
    std::string temp = "";
    // Changes the header format if a day has passes
    if (hour % 24 == 0) {
        temp += name + " | Day: " + std::to_string(hour / 24) + "\n";
    } else {
        temp += name + " | Hour: " + std::to_string(hour) + "\n";
    }
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

void City::run() {
    // Generates the output file
    std::fstream output("output.txt", std::ios::out);
    // Outputs the beginning stats
    output << getStats() << std::endl;
    // Runs until every denizen is a zombie
    for (int i = 0; stats["Zombie"] != 2000; i++) {
        // Iterates through each district
        for (auto itr = districts.begin()++; itr != districts.end(); itr++) {
            // Updates current district
            itr->update();
        }
        // Checks every every denizen within the city to see if they would like to migrate
        migrate();
        updateStats();
        // Outputs current stats to the terminal
        std::cout << getStats() << std::endl;
        // Outputs stats to the output file if a day has passed
        if (hour % 24 == 0) {
            output << getStats() << std::endl;
        }
    }
    output << "After " << std::to_string(hour) << " hours, all denizens have been zombified!" << std::endl;
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
    // Array holding all possible denizen types
    std::string type[4] = { "Ignorant", "Alarmed", "Zombie", "Doctor" };
    // Resets the city stats to 0
    for (int i = 0; i < 4; i++) {
        stats[type[i]] = 0;
    }
    // Updates the city stats for the new time click
    for (auto itr = districts.begin(); itr != districts.end(); itr++) {
        for (int i = 0; i < 4; i++) {
            stats[type[i]] += itr->stats[type[i]];
        }
    }
    hour++;
}

std::vector<std::string> City::feedNames(std::string directory) {
    std::string name;
    std::vector<std::string> names;
    std::ifstream input;
    // EXCEPTION HANDLING
    try {
        input.open(directory);
        while (getline(input, name)) {
            names.push_back(name);
        }
    } catch (std::ifstream::failure) {
        std::cout << "Exception: Cannot read '" << directory << "'" << std::endl;
    }
    return names;
}