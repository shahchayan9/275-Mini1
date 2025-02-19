#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <omp.h>

std::vector<CollisionData> DataLoader::loadCSV(const std::string& filename) {
    std::vector<CollisionData> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return data;
    }

    std::getline(file, line); // Skip header

    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line); // Store lines for parallel processing
    }
    file.close();

    // Create per-thread storage to avoid concurrent writes
    std::vector<std::vector<CollisionData>> thread_data(omp_get_max_threads());

    // Parallel processing of CSV rows
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        std::vector<CollisionData>& local_data = thread_data[thread_id];

        #pragma omp for
        for (size_t i = 0; i < lines.size(); ++i) {
            std::stringstream ss(lines[i]);
            std::string id, date, borough, injured, killed;

            std::getline(ss, id, ',');
            std::getline(ss, date, ',');
            std::getline(ss, borough, ',');
            std::getline(ss, injured, ',');
            std::getline(ss, killed, ',');

            // Trim spaces
            injured.erase(std::remove_if(injured.begin(), injured.end(), isspace), injured.end());
            killed.erase(std::remove_if(killed.begin(), killed.end(), isspace), killed.end());

            int persons_injured = 0, persons_killed = 0;
            if (!injured.empty() && std::all_of(injured.begin(), injured.end(), ::isdigit))
                persons_injured = std::stoi(injured);
            if (!killed.empty() && std::all_of(killed.begin(), killed.end(), ::isdigit))
                persons_killed = std::stoi(killed);

            // Store result in thread-local storage
            local_data.emplace_back(id, date, borough, persons_injured, persons_killed);
        }
    }

    // Merge all thread-local data into `data`
    for (const auto& local_vec : thread_data) {
        data.insert(data.end(), local_vec.begin(), local_vec.end());
    }

    return data;
}
