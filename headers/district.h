///////////////////////////////////////////////////////////////////////
//  Header file for Denizen Class                                    //
//  Developed by Jacob Ojennus, Zach Marble, and Garrett Daviscourt  //
//  For CS-274-1                                                     //
///////////////////////////////////////////////////////////////////////

#ifndef DISTRICT_H
#define DISTRICT_H

#include <vector>
#include <map>
#include "denizen.h"

// District class
// Manages the denizen class
// Allows all denizens in the district to interact
class District {
private:
    friend class City; // Gives the city class access to District atrributes
    std::string name; // Holds name
    std::vector<Denizen*> population; // Holds denizens 
    std::map<std::string, int> stats; // Holds stats
public:
    // Constructor
    District(int population, std::string name = "Not Assigned", bool patientZero = false, bool medicalHill = false);
    // Getters
    std::string getName();
    std::string getStats();
    // Update Function
    // Allows all denizens to interact with each other
    void update();
    // Update Stats Function
    // Adds or removes a denizen from the stat pool
    void updateStats(Denizen* den, bool add = true);
};

#endif