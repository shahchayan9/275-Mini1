#include <iostream>
#include <chrono>
#include "DataLoader.h"
#include "SearchEngine.h"

int main() {
    std::string filename = "/Users/ankitojha/mini1/data/Motor_Vehicle_Collisions_-_Crashes_20250123.csv";
    // /Users/ankitojha/mini1/data/Motor_Vehicle_Collisions_-_Crashes_20250123.csv

    // Benchmark start
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::vector<CollisionData> data = DataLoader::loadCSV(filename);
    
    // Benchmark end
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Data loaded in " << std::chrono::duration<double>(end_time - start_time).count() << " seconds\n";

    if (data.empty()) {
        std::cerr << "No data loaded. Exiting.\n";
        return 1;
    }

    std::cout << "Total records loaded: " << data.size() << std::endl;

    // Search Example: Borough
    std::string target_borough = "BROOKLYN";
    auto brooklyn_collisions = SearchEngine::searchByBorough(data, target_borough);
    std::cout << "Collisions in " << target_borough << ": " << brooklyn_collisions.size() << std::endl;

    // Search Example: Injury Threshold
    int min_injuries = 3;
    auto severe_collisions = SearchEngine::searchByInjuryThreshold(data, min_injuries);
    std::cout << "Collisions with >= " << min_injuries << " injuries: " << severe_collisions.size() << std::endl;

    return 0;
}
