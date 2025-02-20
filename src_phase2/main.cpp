#include <iostream>
#include <chrono>
#include "DataLoader.h"
#include "SearchEngine.h"

int main() {
    std::string filename = "../data/Motor_Vehicle_Collisions_-_Crashes_20250123.csv";
    //int num_threads = omp_get_max_threads();  // Get max threads OpenMP will use
    //std::cout << "Using " << num_threads << " threads.\n";

    // Parallel Data Load
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<CollisionData> data = DataLoader::loadCSV(filename);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel Data Load: " << std::chrono::duration<double>(end_time - start_time).count() << " seconds\n";

    if (data.empty()) {
        std::cerr << "No data loaded. Exiting.\n";
        return 1;
    }

    std::cout << "Total records loaded: " << data.size() << std::endl;

    // Parallel Borough Search
    std::string target_borough = "BROOKLYN";
    start_time = std::chrono::high_resolution_clock::now();
    auto brooklyn_collisions = SearchEngine::searchByBorough(data, target_borough);
    end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel Borough Search: " << std::chrono::duration<double>(end_time - start_time).count() << " seconds\n";

    // Parallel Injury Search
    int min_injuries = 3;
    start_time = std::chrono::high_resolution_clock::now();
    auto severe_collisions = SearchEngine::searchByInjuryThreshold(data, min_injuries);
    end_time = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel Injury Search: " << std::chrono::duration<double>(end_time - start_time).count() << " seconds\n";

    return 0;
}
