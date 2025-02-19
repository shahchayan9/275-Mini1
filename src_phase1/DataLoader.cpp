#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm> // For std::remove_if

std::vector<CollisionData> DataLoader::loadCSV(const std::string& filename) {
    std::vector<CollisionData> data;
    std::ifstream file(filename);
    std::string line, id, date, borough, injured, killed;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, id, ',');
        std::getline(ss, date, ',');
        std::getline(ss, borough, ',');
        std::getline(ss, injured, ',');
        std::getline(ss, killed, ',');

        // Remove leading/trailing spaces
        injured.erase(std::remove_if(injured.begin(), injured.end(), isspace), injured.end());
        killed.erase(std::remove_if(killed.begin(), killed.end(), isspace), killed.end());

        int persons_injured = 0, persons_killed = 0;
        try {
            // Convert only if valid numeric data is present
            if (!injured.empty() && std::all_of(injured.begin(), injured.end(), ::isdigit))
                persons_injured = std::stoi(injured);
            if (!killed.empty() && std::all_of(killed.begin(), killed.end(), ::isdigit))
                persons_killed = std::stoi(killed);
        } catch (const std::exception& e) {
            std::cerr << "Skipping row due to invalid data: " << line << " | Error: " << e.what() << std::endl;
            continue; // Skip this row and proceed to the next one
        }

        // Store valid data
        data.emplace_back(id, date, borough, persons_injured, persons_killed);
    }

    file.close();
    return data;
}
