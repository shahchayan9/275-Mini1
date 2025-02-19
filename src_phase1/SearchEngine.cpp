#include "SearchEngine.h"

std::vector<CollisionData> SearchEngine::searchByBorough(const std::vector<CollisionData>& data, const std::string& borough) {
    std::vector<CollisionData> result;
    for (const auto& record : data) {
        if (record.borough == borough) {
            result.push_back(record);
        }
    }
    return result;
}

std::vector<CollisionData> SearchEngine::searchByInjuryThreshold(const std::vector<CollisionData>& data, int min_injuries) {
    std::vector<CollisionData> result;
    for (const auto& record : data) {
        if (record.persons_injured >= min_injuries) {
            result.push_back(record);
        }
    }
    return result;
}
