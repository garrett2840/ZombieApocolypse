#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <list>
#include "district.h"

class City {
private:
    std::string name; // Holds name 
    std::list<District> districts; // Holds districts
    std::map<std::string, int> stats; // Holds stats for the city
    int hour = 0; // Holds the current hour
public:
    // Constructor
    City(int population, std::string name);
    // Getters
    std::string getStats();
    // Run Function
    void run(int days);
    // Migrate Function
    void migrate();
    // Update Stats Function
    void updateStats();
    // Name Function
    std::vector<std::string> feedNames(std::string directory);
};

#endif