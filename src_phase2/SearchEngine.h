#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "CollisionData.h"
#include <vector>
#include <string>

class SearchEngine {
public:
    static std::vector<CollisionData> searchByBorough(const std::vector<CollisionData>& data, const std::string& borough);
    static std::vector<CollisionData> searchByInjuryThreshold(const std::vector<CollisionData>& data, int min_injuries);
};

#endif
