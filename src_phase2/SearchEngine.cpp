#include "SearchEngine.h"
#include <omp.h>

std::vector<CollisionData> SearchEngine::searchByBorough(const std::vector<CollisionData>& data, const std::string& borough) {
    std::vector<CollisionData> result;
    std::vector<std::vector<CollisionData>> thread_results(omp_get_max_threads());

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        std::vector<CollisionData>& local_result = thread_results[thread_id];

        #pragma omp for nowait
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].borough == borough) {
                local_result.push_back(data[i]);
            }
        }
    }

    for (auto& vec : thread_results) {
        result.insert(result.end(), vec.begin(), vec.end());
    }
    return result;
}

std::vector<CollisionData> SearchEngine::searchByInjuryThreshold(const std::vector<CollisionData>& data, int min_injuries) {
    std::vector<CollisionData> result;
    std::vector<std::vector<CollisionData>> thread_results(omp_get_max_threads());

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        std::vector<CollisionData>& local_result = thread_results[thread_id];

        #pragma omp for nowait
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].persons_injured >= min_injuries) {
                local_result.push_back(data[i]);
            }
        }
    }

    for (auto& vec : thread_results) {
        result.insert(result.end(), vec.begin(), vec.end());
    }
    return result;
}
